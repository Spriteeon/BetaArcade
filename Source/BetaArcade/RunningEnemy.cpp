// Fill out your copyright notice in the Description page of Project Settings.

#include "RunningEnemy.h"
#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "GameFramework/Actor.h"

ARunningEnemy::ARunningEnemy()
{

	health = 100;
	points = 100;
	speed = 10.0f;

}

// Called when the game starts or when spawned
void ARunningEnemy::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ARunningEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARunningEnemy::UpdatePosition()
{

}

void ARunningEnemy::Attack()
{

}

void ARunningEnemy::Die()
{

}
