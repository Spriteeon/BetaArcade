// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "Kismet/GameplayStatics.h"
#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "Monster.h"
#include "BetaArcadeCharacter.generated.h"

UENUM(BlueprintType)
namespace CharacterState // Namespace because enum was throwing "Member ... is not a type name"
{
	enum State
	{
		None		UMETA(DisplayName = "None"),
		Jumping		UMETA(DisplayName = "Jumping"),
		Vaulting	UMETA(DisplayName = "Vaulting"),
		Sliding		UMETA(DisplayName = "Sliding"),
		Combat		UMETA(DisplayName = "Combat"),
		Swarm		UMETA(DisplayName = "Swarm"),
	};
}

UENUM(BlueprintType)
namespace PowerState
{
	enum State
	{
		None		UMETA(DisplayName = "None"),
		SpeedBoost	UMETA(DisplayName = "SpeedBoost"),
		Magnet		UMETA(DisplayName = "Magnet"),
		SecondWind	UMETA(DisplayName = "SecondWind"),
		ScoreBonus	UMETA(DisplayName = "ScoreBonus"),
		ExtraLife	UMETA(DisplayName = "ExtraLife"),
		LightBall	UMETA(DisplayName = "LightBall"),
		FullLight	UMETA(DisplayName = "FullLight"),
		SporeEffect	UMETA(DisplayName = "SporeEffect"),
	};
}

UCLASS(config = Game)
class ABetaArcadeCharacter : public ACharacter
{
	GENERATED_BODY()

		/** Camera boom positioning the camera behind the character */
		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* PlayerCamera;

public:
	ABetaArcadeCharacter();	

	UPROPERTY(BlueprintReadOnly)
		FVector playerDirection = { 0,0,0 };
	UPROPERTY(BlueprintReadWrite)
		FRotator currentMonsterRotation = { 0,0,0 };
	UPROPERTY(BlueprintReadWrite)
		FVector currentCamPosition = { 0,0,0 };
	UPROPERTY(BlueprintReadWrite)
		FRotator currentCamRotation = { 0,0,0 };
	UPROPERTY(BlueprintReadWrite)
		FRotator currentPlayerRotation = { 0,0,0 };

	UPROPERTY(BlueprintReadWrite)
		FKey playerKeyPressed;

	UPROPERTY(BlueprintReadWrite)
		bool swarmReacting = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool canMove = true;

	UPROPERTY(BlueprintReadWrite)
		bool inCombat = false;

	UPROPERTY(BlueprintReadWrite)
		bool lightWidgetActive = false;

protected:
	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	FRotator currentRot;
	FVector Direction;
	UPROPERTY(BlueprintReadWrite)
		FVector initialPos;

	UFUNCTION(BlueprintImplementableEvent)
		void AnimationState();

	// FRAN STUFF
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TEnumAsByte<CharacterState::State> characterState;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AMonster* monster;

	UPROPERTY(EditAnywhere)
		AActor* floor;

	UPROPERTY()
		UCharacterMovementComponent* playerMovement;
	UPROPERTY(BlueprintReadWrite)
		float initialMapSpeed = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float slideTime = 0.0f; // How long the player slides for
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float vaultTime = 0.0f; // How long the player vaults for

	const int MAX_PLAYER_LIVES = 3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int playerLives = 0;

	//Light bar- BETH
	const int MAX_LIGHT_CAPACITY = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int lightCapacity = 0;

	//Points system - BETH
	UPROPERTY()
		int playerScore = 0;

	// Constant run toggle for testing!
	UPROPERTY(EditAnywhere)
		bool constantRun = false;

	bool hasCameraRotated = false;
	UPROPERTY(BlueprintReadWrite)
		bool isCameraZoomed = false;

	UPROPERTY(EditAnywhere)
		FRotator cameraFlipRotation = { 5,-180,0 };
	UPROPERTY(EditAnywhere)
		FVector camZoomPos = { -360,40,100 };
	FRotator initialCamRot;
	FVector initialCamPos;

	UPROPERTY(BlueprintReadWrite)
		bool isJumping = false;
	UPROPERTY(BlueprintReadWrite)
		bool canVault = false;

	UPROPERTY(BlueprintReadWrite)
		FKey currentSwarmKey;

	UPROPERTY(BlueprintReadWrite)
		bool combatActive = false;
	UPROPERTY(BlueprintReadWrite)
	int bonusChance = 0;

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

	virtual void BeginPlay() override;

	// State control
	void HandleState();
	UFUNCTION(BlueprintCallable)
		void EnterCombat();
	UFUNCTION(BlueprintCallable)
		void EndCombat();
	UFUNCTION(BlueprintImplementableEvent)
		void CameraFlip();
	UFUNCTION(BlueprintImplementableEvent)
		void PlayCombatSound();
	void CombatBonus();
	void GiveBonus();

	void BetaJump();
	void JumpEndCheck();
	void BetaJumpStop();

	UFUNCTION(BlueprintCallable)
		bool StartSlide();
	void Slide();
	UFUNCTION(BlueprintCallable)
		void StopSliding();

	UFUNCTION(BlueprintImplementableEvent)
		void VaultControl();
	UFUNCTION(BlueprintCallable)
		bool StartVault();
	UFUNCTION(BlueprintCallable)
		void StopVaulting();

	void DodgeCheck(FKey playerKeyPressed);

	UFUNCTION(BlueprintImplementableEvent)
		void Combat();

	UFUNCTION(BlueprintImplementableEvent)
		void GetMapSpeed();

	// Notifies UI of change to value
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void LivesEvent();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void GameOver();

public:
	virtual void Tick(float DeltaTime) override;

	//FRAN- PowerUp State
	UPROPERTY(BlueprintReadWrite)
		TEnumAsByte<PowerState::State> currentPowerState;

	// LIVES
	UFUNCTION(BlueprintCallable)
		int GetPlayerLives() { return playerLives; };
	UFUNCTION(BlueprintCallable)
		void AddPlayerLives(int lives) { if ((playerLives + lives) <= MAX_PLAYER_LIVES) { playerLives += lives; LivesEvent(); } }; // Adds however many lives are passed in, to take away lives just pass in a negative

	bool GetSwarmReaction() { return swarmReacting; };
	UFUNCTION(BlueprintCallable)
		void GetSwarmKey(FKey key) { currentSwarmKey = key;};

	// SPEED
	UFUNCTION(BlueprintCallable)
		void ResetPlayerSpeed() { SetPlayerSpeed(initialMapSpeed); }; // Sets speed to original value
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void SetPlayerSpeed(float speed);

	UFUNCTION(BlueprintImplementableEvent)
	void LightWidgetOn();
	UFUNCTION(BlueprintImplementableEvent)
	void LightWidgetOff();

	//BETH - 

	//PICKUPS & HOTBAR 
	/*UFUNCTION(BlueprintCallable)
		void UsePickUp(class APickUpBase* PickUp);*/
	UFUNCTION(BlueprintCallable)
		void SortPickUp(class APickUpBase* PickUp);

	UFUNCTION(BlueprintCallable)
		int GetLightAmount() { return lightCapacity; };

	UFUNCTION(BlueprintCallable, category = "PickUps")
		void AddLightAmount(int lightamount) { lightCapacity += lightamount; };

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void MagnetActivatedAction();

	UFUNCTION(BlueprintCallable)
		void SecondWindAction();

	UFUNCTION(BlueprintCallable)
	bool LightMetreFull();
	
	UPROPERTY(BlueprintReadWrite)
	bool isSecondWindInHotbar = false;
	
	UPROPERTY(BlueprintReadWrite)
	bool hasHadLifeRemoved = false;

	UPROPERTY(BlueprintReadWrite)
	bool isMagnetActive;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class UHotbarComp* Hotbar;

	//Points
	UPROPERTY(BlueprintReadWrite)
		int scoreMultiplier = 1;

	UFUNCTION(BlueprintCallable)
		int GetPlayerScore() { return playerScore; };

	UFUNCTION(BlueprintCallable)
		void AddPointsToScore(int points) { playerScore += (points * scoreMultiplier); };

};