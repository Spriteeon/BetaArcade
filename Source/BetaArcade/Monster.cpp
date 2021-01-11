// Fill out your copyright notice in the Description page of Project Settings.

#include "Monster.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AMonster::AMonster()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
	CapsuleComponent->InitCapsuleSize(42.f, 96.0f);
	RootComponent = CapsuleComponent;

}

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMonster::UpdateMonsterDistance(int playerLives, float currentPlayerXPos)
{

	switch (playerLives)
	{
	case 3:
		newMonsterPos.X = currentPlayerXPos - playerThreeLivesDistance;
		break;
	case 2:
		newMonsterPos.X = currentPlayerXPos - playerTwoLivesDistance;
		break;
	case 1:
		newMonsterPos.X = currentPlayerXPos - playerOneLifeDistance;
		break;
	case 0:
		// Player is Dead
		break;
	default:
		break;
	}

	this->SetActorLocation(newMonsterPos);
}

// Called to bind functionality to input
//void AMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//	Super::SetupPlayerInputComponent(PlayerInputComponent);
//
//}