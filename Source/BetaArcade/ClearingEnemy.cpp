// Fill out your copyright notice in the Description page of Project Settings.

#include "ClearingEnemy.h"
#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "GameFramework/Actor.h"

AClearingEnemy::AClearingEnemy()
{

	health = 100;
	points = 100;
	speed = 10.0f;

}

// Called when the game starts or when spawned
void AClearingEnemy::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AClearingEnemy::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);

	if (health <= 0)
	{
		Die();
	}

	UpdatePosition();

}

void AClearingEnemy::UpdatePosition()
{

}

void AClearingEnemy::Attack()
{

}

void AClearingEnemy::Die()
{

}

// Called to bind functionality to input
void AClearingEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}