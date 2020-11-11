// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "ClearingEnemy.generated.h"

/**
 * 
 */
UCLASS()
class BETAARCADE_API AClearingEnemy : public AEnemyBase
{
	GENERATED_BODY()
	
public:

	AClearingEnemy();

protected:

	virtual void BeginPlay() override;

public:

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Tick(float DeltaTime) override;

	virtual void UpdatePosition() override;
	virtual void Attack() override;
	virtual void Die() override;

};
