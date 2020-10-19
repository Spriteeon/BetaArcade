// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyBase.generated.h"

UCLASS()
class BETAARCADE_API AEnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyBase();

protected:
	// Called when the game starts or when spawned
	//virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	int health{ 0 };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	int points{ 0 };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	float speed{ 0.0f };

	virtual void UpdatePosition() {};
	virtual void Attack() {};
	virtual void Die() {};

};
