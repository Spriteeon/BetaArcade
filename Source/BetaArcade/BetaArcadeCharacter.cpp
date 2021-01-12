// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "BetaArcadeCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Engine.h"
#include "TimerManager.h"
#include "PickUps+Hotbar/PickUpBase.h"
#include "PickUps+Hotbar/HotbarComp.h"

//////////////////////////////////////////////////////////////////////////
// ABetaArcadeCharacter

ABetaArcadeCharacter::ABetaArcadeCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 500.0f;
	CameraBoom->bUsePawnControlRotation = true;

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	playerLives = MAX_PLAYER_LIVES;
	characterState = CharacterState::State::None;

	playerMovement = GetCharacterMovement();
	currentCamRotation = { -10,0,0 };
	currentCamPosition = CameraBoom->GetComponentLocation();
	currentMonsterRotation = { 0,0,0 };

	Direction = GetActorForwardVector();
	playerDirection = GetActorForwardVector();

	//BETH - Hotbar component initialisation.
	Hotbar = CreateDefaultSubobject<UHotbarComp>("Hotbar");
	Hotbar->NumSlots = 4;

	playerScore = 0.f;
}

//////////////////////////////////////////////////////////////////////////
// Input

void ABetaArcadeCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ABetaArcadeCharacter::BetaJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ABetaArcadeCharacter::BetaJumpStop);
	PlayerInputComponent->BindAction("FlipCamera", IE_Pressed, this, &ABetaArcadeCharacter::EnterCombat);
	PlayerInputComponent->BindAction("Dodge", IE_Pressed, this, &ABetaArcadeCharacter::DodgeCheck);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABetaArcadeCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABetaArcadeCharacter::MoveRight);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &ABetaArcadeCharacter::OnResetVR);
}

void ABetaArcadeCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddPointsToScore(1 * scoreMultiplier);

	HandleState();
}

//BETH - 

//Sort Pick Ups into instant use or hotbar.
void ABetaArcadeCharacter::SortPickUp(class APickUpBase* PickUp)
{
	if (PickUp->PickUpID <= 3 && PickUp != NULL)
	{
		
		Hotbar->AddPickUp(PickUp);

	}

	else if (PickUp->PickUpID == 4 && PickUp != NULL)
	{
		isSecondWindInHotbar = true;
		UE_LOG(LogTemp, Log, TEXT("second wind in hb is true"));

		Hotbar->AddPickUp(PickUp);
	}

	else if (PickUp->PickUpID >= 6 && PickUp != NULL)
	{
		PickUp->ItemAction(this);
	}
}

void ABetaArcadeCharacter::SecondWindAction()
{
		currentPowerState = PowerState::State::SecondWind;
		AddPlayerLives(1);
		Hotbar->RemovePickUp(4);
		isSecondWindInHotbar = false;
	
}

//Sets power state of player when light meter is full. 
bool ABetaArcadeCharacter::LightMetreFull()
{
	if (lightCapacity >= 100)
	{
		currentPowerState = PowerState::State::FullLight;
		return true;
	}
	else
	{
		return false;
	}

}

// FRAN - State control
void ABetaArcadeCharacter::HandleState()
{
	switch (characterState)
	{
	case CharacterState::State::None:
		break;

	case CharacterState::State::Jumping:
		JumpEndCheck();
		break;

	case CharacterState::State::Vaulting:
		break;

	case CharacterState::State::Sliding:
		break;

	case CharacterState::State::Combat:
		Combat();
		break;

	case CharacterState::State::Swarm:
		break;

	default:
		break;
	}

	AnimationState();
}

void ABetaArcadeCharacter::EnterCombat()
{
	if ((!inCombat) && (LightMetreFull())) // not currently in combat
	{
		bonusChance = 0;
		currentCamRotation = cameraFlipRotation;
		currentCamPosition = camZoomPos;
		PlayCombatSound();

		combatActive = true;
		characterState = CharacterState::State::Combat;

		CameraFlip();
		inCombat = !inCombat;
	}
}

void ABetaArcadeCharacter::EndCombat()
{
	if (inCombat)
	{
		PlayCombatSound();
		inCombat = !inCombat;
		GiveBonus();
		currentCamRotation = initialCamRot;
		currentCamPosition = initialCamPos;

		combatActive = false;
		bonusChance = 0;

		CameraFlip();
		characterState = CharacterState::State::None;
	}
}

void ABetaArcadeCharacter::CombatBonus()
{
	if(bonusChance < 100)
		bonusChance++;
}

void ABetaArcadeCharacter::GiveBonus()
{
	if (bonusChance >= 20)
	{
		AddPlayerLives(1);
		AddPointsToScore(300);
	}
	else
	{
		AddPointsToScore(100);
	}
}

void ABetaArcadeCharacter::BetaJump()
{
	if (characterState != CharacterState::Combat)
	{
		if (canVault)
		{
			VaultControl();
		}
		else if ((characterState == CharacterState::None) && (canMove))
		{
			isJumping = true;
			characterState = CharacterState::State::Jumping;
			Jump();
		}
	}
	else
	{
		CombatBonus();
	}
}

void ABetaArcadeCharacter::JumpEndCheck()
{
	if (!isJumping) // set on hit floor
	{
		characterState = CharacterState::State::None;
	}
}

void ABetaArcadeCharacter::BetaJumpStop() // UE4 func - called in Jump()
{
	StopJumping();
}

bool ABetaArcadeCharacter::StartSlide()
{
	if (characterState == CharacterState::State::None)
	{
		characterState = CharacterState::State::Sliding;
		return true;
	}

	return false;
}

void ABetaArcadeCharacter::StopSliding()
{
	characterState = CharacterState::State::None;
}

bool ABetaArcadeCharacter::StartVault()
{
	if (characterState == CharacterState::State::None)
	{
		characterState = CharacterState::State::Vaulting;
		Jump();

		return true;
	}
	
	return false;
}

void ABetaArcadeCharacter::StopVaulting()
{
	StopJumping();
	characterState = CharacterState::State::None;
}

void ABetaArcadeCharacter::DodgeCheck(FKey playerKeyPressed)
{
	if (playerKeyPressed == currentSwarmKey)
	{
		swarmReacting = true;
	}
	else
	{
		swarmReacting = false;
	}

}

void ABetaArcadeCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ABetaArcadeCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value > 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		AddMovementInput(Direction, Value);
	}
}

void ABetaArcadeCharacter::MoveRight(float Value)
{
	FRotator Left = { 0,-50,0 };
	FRotator Right = { 0,50,0 };

	FVector leftMove = { 0,-14,0 };
	FVector rightMove = { 0,14,0 };

	if (((characterState == CharacterState::State::None) && (canMove)) || ((characterState == CharacterState::State::Swarm) && (canMove)))
	{
		if ((Controller != NULL) && (Value != 0.0f))
		{
			FVector pos = GetActorLocation();
			if (Value < 0) // A
			{
				if (GetActorLocation().Y >= -240)
				{
					Left += currentPlayerRotation;
					leftMove += pos;
					SetActorRotation(FMath::Lerp(GetActorRotation(), Left, 0.6f));
					SetActorLocation(leftMove, false, 0, ETeleportType::None);
				}
			}
			else if (Value > 0)
			{
				if (GetActorLocation().Y <= 240)
				{
					Right += currentPlayerRotation;
					rightMove += pos;
					SetActorRotation(FMath::Lerp(GetActorRotation(), Right, 0.6f));
					SetActorLocation(rightMove, false, 0, ETeleportType::None);
				}
			}
			Direction = GetActorForwardVector();
		}

		if (Value == 0)
		{
			SetActorRotation(FMath::Lerp(GetActorRotation(), currentPlayerRotation, 0.5f));
			Direction = GetActorForwardVector();
		}
	}
}

// Called when the game starts or when spawned
void ABetaArcadeCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetMapSpeed(); // Stores starting speed
	initialPos = GetActorLocation();

	initialCamPos = CameraBoom->GetRelativeLocation();
	initialCamRot = CameraBoom->GetRelativeRotation();

	currentCamRotation = initialCamRot;
	currentCamPosition = initialCamPos;
}