// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "BetaArcadeCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Engine.h"
#include "TimerManager.h"

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

	/*camera->ViewPitchMax = maxCameraPitch;
	camera->ViewPitchMin = minCameraPitch;
	camera->ViewYawMax = maxCameraYaw;
	camera->ViewYawMin = minCameraYaw;*/

	playerLives = MAX_PLAYER_LIVES;
	characterState = CharacterState::State::None;

	playerMovement = GetCharacterMovement();
	currentCamRotation = { -10,0,0 }; 
	currentCamPosition = CameraBoom->GetComponentLocation();

	Direction = GetActorForwardVector();
}

//////////////////////////////////////////////////////////////////////////
// Input

void ABetaArcadeCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ABetaArcadeCharacter::BetaJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ABetaArcadeCharacter::BetaJumpStop);
	PlayerInputComponent->BindAction("Swarm", IE_Pressed, this, &ABetaArcadeCharacter::SwarmReaction);
	PlayerInputComponent->BindAction("Swarm", IE_Released, this, &ABetaArcadeCharacter::SwarmReactionStop);
	PlayerInputComponent->BindAction("FlipCamera", IE_Pressed, this, &ABetaArcadeCharacter::CameraFlipControl);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABetaArcadeCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABetaArcadeCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	//PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	//PlayerInputComponent->BindAxis("TurnRate", this, &ABetaArcadeCharacter::TurnAtRate);
	/*PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ABetaArcadeCharacter::LookUpAtRate);*/
	/*PlayerInputComponent->BindAction("CameraZoomIn", IE_Pressed, this, &ABetaArcadeCharacter::CameraZoomIn);
	PlayerInputComponent->BindAction("CameraZoomIn", IE_Released, this, &ABetaArcadeCharacter::CameraZoomIn);
	PlayerInputComponent->BindAction("CameraZoomOut", IE_Pressed, this, &ABetaArcadeCharacter::CameraZoomOut);
	PlayerInputComponent->BindAction("CameraZoomOut", IE_Released, this, &ABetaArcadeCharacter::CameraZoomOut);*/

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &ABetaArcadeCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ABetaArcadeCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &ABetaArcadeCharacter::OnResetVR);
}

void ABetaArcadeCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	HandleState();
}

// FRAN - State control
void ABetaArcadeCharacter::HandleState()
{
	if (constantRun)
		MoveForward(1.0f);

	switch (characterState)
	{
	case CharacterState::State::None:
		break;

	case CharacterState::State::Jumping:
		JumpEndCheck();
		break;

	case CharacterState::State::Vaulting:
		Vault();
		break;

	case CharacterState::State::Sliding:
		Slide();
		break;

	default:
		break;
	}
}

void ABetaArcadeCharacter::CameraFlipControl()
{
	if (!isCameraBackwards) // camera is currently facing forward
	{
		currentCamRotation += cameraFlipRotation;
		currentCamPosition -= camZoomPos;
	}
	else
	{
		currentCamRotation -= cameraFlipRotation;
		currentCamPosition += camZoomPos;
	}

	CameraFlip();
	isCameraBackwards = !isCameraBackwards;
}

void ABetaArcadeCharacter::BetaJump()
{
	if (canVault)
	{
		VaultControl();
	}
	else if (characterState == CharacterState::None)
	{
		isJumping = true;
		UE_LOG(LogTemp, Log, TEXT("Jump"));
		characterState = CharacterState::State::Jumping;
		Jump();
	}
}

void ABetaArcadeCharacter::JumpEndCheck()
{
	if (!isJumping)
	{
		characterState = CharacterState::State::None;
	}
}

void ABetaArcadeCharacter::BetaJumpStop()
{
	UE_LOG(LogTemp, Log, TEXT("JumpSTOP"));
	StopJumping();
}

bool ABetaArcadeCharacter::StartSlide()
{
	if (characterState == CharacterState::State::None)
	{
		characterState = CharacterState::State::Sliding;
		
		currentRot = GetActorRotation();
		FRotator slideRot = { 90, 0, 0 };
		currentPlayerRotation += slideRot;

		UE_LOG(LogTemp, Log, TEXT("Slide"));
		return true;
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Can't slide"));
		return false;
	}
}

void ABetaArcadeCharacter::Slide()
{	
	SetPlayerSpeed(playerSpeed * 0.7);
	SetActorRelativeRotation(currentPlayerRotation, false, 0, ETeleportType::None);
}

void ABetaArcadeCharacter::StopSliding()
{
	UE_LOG(LogTemp, Log, TEXT("SlideSTOP"));

	FRotator resetRot = { 90,0,0 };
	currentPlayerRotation -= resetRot;

	ResetPlayerSpeed();
	SetActorRelativeRotation(currentPlayerRotation, false, 0, ETeleportType::None);

	characterState = CharacterState::State::None;
}

bool ABetaArcadeCharacter::StartVault()
{
	if (characterState == CharacterState::State::None)
	{
		characterState = CharacterState::State::Vaulting;
		Jump();

		currentRot = GetActorRotation();
		FRotator vaultRot = { -90, 0, 0 };
		currentPlayerRotation += vaultRot;
		Vault();

		UE_LOG(LogTemp, Log, TEXT("Vault"));
		return true;
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Can't vault"));
		return false;
	}
}

void ABetaArcadeCharacter::Vault()
{
	SetActorRelativeRotation(currentPlayerRotation, false, 0, ETeleportType::None);
}

void ABetaArcadeCharacter::StopVaulting()
{
	StopJumping();
	UE_LOG(LogTemp, Log, TEXT("VaultSTOP"));
	FRotator resetRot = { -90,0,0 };
	currentPlayerRotation -= resetRot;
	SetActorRelativeRotation(resetRot, false, 0, ETeleportType::None);
	characterState = CharacterState::State::None;
}

void ABetaArcadeCharacter::LeftTurn()
{
	currentCamRotation += { 0, -60, 0 };
	currentPlayerRotation += {0, -60, 0};

	SetActorRotation(FMath::Lerp(GetActorRotation(), currentPlayerRotation, 0.7f));
	Direction = GetActorForwardVector();
}

void ABetaArcadeCharacter::RightTurn()
{
	currentCamRotation += { 0, 60, 0 };
	currentPlayerRotation += {0, 60, 0};

	SetActorRotation(FMath::Lerp(GetActorRotation(), currentPlayerRotation, 0.7f));
	Direction = GetActorForwardVector();
}

void ABetaArcadeCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ABetaArcadeCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
}

void ABetaArcadeCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
}

//// FRAN - CAMERA ZOOM
//void ABetaArcadeCharacter::CameraZoomIn()
//{
//	if (CameraBoom->TargetArmLength - cameraZoomValue > minCameraZoom)
//		CameraBoom->TargetArmLength -= cameraZoomValue;
//}
//
//void ABetaArcadeCharacter::CameraZoomOut()
//{
//	if (CameraBoom->TargetArmLength + cameraZoomValue < maxCameraZoom)
//		CameraBoom->TargetArmLength += cameraZoomValue;
//}
//
//void ABetaArcadeCharacter::TurnAtRate(float Rate)
//{
//	// calculate delta for this frame from the rate information
//	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
//}
//
//void ABetaArcadeCharacter::LookUpAtRate(float Rate)
//{
//	// calculate delta for this frame from the rate information
//	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
//}

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
	FRotator Left = { 0,-30,0 };
	FRotator Right = FRotator{ 0,30,0 };

	if (characterState == CharacterState::State::None)
	{
		if ((Controller != NULL) && (Value != 0.0f))
		{
			if (Value < 0) // A
			{
				Left += currentPlayerRotation;
				SetActorRotation(FMath::Lerp(GetActorRotation(), Left, 0.5f));
			}
			else if (Value > 0)
			{
				Right += currentPlayerRotation;
				SetActorRotation(FMath::Lerp(GetActorRotation(), Right, 0.5f));
			}
			Direction = GetActorForwardVector();
			MoveForward(1);
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

	playerSpeed = playerMovement->MaxWalkSpeed;
	initialPlayerSpeed = playerMovement->MaxWalkSpeed; // Stores starting speed
}
