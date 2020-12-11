// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Monster.generated.h"

UCLASS()
class BETAARCADE_API AMonster : public APawn
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, Category = "Collision")
		class UCapsuleComponent* CapsuleComponent;

public:

	// Sets default values for this pawn's properties
	AMonster();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	// Called every frame
	//virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void UpdatePosition(FVector pos);

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
