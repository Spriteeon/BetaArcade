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

	UPROPERTY(BlueprintReadOnly, Category = LifeDistance)
		float playerOneLifeDistance = 2000.0f;
	UPROPERTY(BlueprintReadOnly, Category = LifeDistance)
		float playerTwoLivesDistance = 3500.0f;
	UPROPERTY(BlueprintReadOnly, Category = LifeDistance)
		float playerThreeLivesDistance = 5000.0f;

	UFUNCTION(BlueprintCallable)
		void UpdateMonsterDistance(int playerLives, float currentPlayerXPos);

	UPROPERTY(BlueprintReadWrite, Category = MonsterPos)
		FVector newMonsterPos = { 0.0f, 0.0f, 110.0f };

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
