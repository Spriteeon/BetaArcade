// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/GameplayStatics.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BetaArcadeCharacter.generated.h"

UENUM(BlueprintType)
namespace CharacterState // Namespace because enum was throwing "Member ... is not a type name"
{
	enum State
	{
		Running		UMETA(DisplayName = "Running"),
		Jumping		UMETA(DisplayName = "Jumping"),
		Vaulting	UMETA(DisplayName = "Vaulting"),
		Sliding		UMETA(DisplayName = "Sliding"),
	};
}

UENUM(BlueprintType)
namespace PowerState
{
	enum State
	{
		None		UMETA(DisplayName = "None"),
		SpeedBoost	UMETA(DisplayName = "SpeedBoost"),
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
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;
public:
	ABetaArcadeCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

protected:

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);


	// State control
	void HandleState();
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	//PlayerState playerState = PlayerState::Idle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TEnumAsByte<CharacterState::State> characterState;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TEnumAsByte<PowerState::State> powerState;

	void BetaJump();
	void BetaJumpStop();
	void Slide();
	void StopSliding();

	// Swarm stuff
	bool isReacting = false;
	void SwarmReaction() { isReacting = true; }
	void SwarmReactionStop() { isReacting = false; }

	// FRAN - Camera zoom control
	void CameraZoomIn();
	void CameraZoomOut();
	UPROPERTY(EditAnywhere)
		float cameraZoomValue = 0.0f;
	UPROPERTY(EditAnywhere)
		float minCameraZoom = 0.0f;
	UPROPERTY(EditAnywhere)
		float maxCameraZoom = 0.0f;

	const int MAX_PLAYER_LIVES = 3;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		int playerLives = 0;

	// Constant run toggle for testing!
	UPROPERTY(EditAnywhere)
		bool constantRun = false;

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	/*FVector currentPosition;
	FVector GetPlayerPosition();*/

	int GetPlayerLives() { return playerLives; };
	// Adds however many lives are passed in, to take away lives just pass in a negative
	void AddPlayerLives(int lives) { playerLives += lives; };

	bool GetSwarmReaction() { return isReacting; }
};
