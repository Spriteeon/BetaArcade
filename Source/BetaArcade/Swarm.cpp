// Fill out your copyright notice in the Description page of Project Settings.

#include "Swarm.h"
#include "BetaArcadeCharacter.h"

// Sets default values
ASwarm::ASwarm()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Spawned in when player triggers spawn box
}

// Called when the game starts or when spawned
void ASwarm::BeginPlay()
{
	Super::BeginPlay();
}

void ASwarm::ChooseKey()
{
	int randKey = rand() % 3;

	switch (randKey)
	{
	case 0: 
		qteKey = EKeys::Q;
		qteText = "Q";
		break;

	case 1:
		qteKey = EKeys::W;
		qteText = "W";
		break;

	case 2:
		qteKey = EKeys::E;
		qteText = "E";
		break;

	default:
		break;
	}

	player->GetSwarmKey(qteKey, qteText);
}

// Called every frame
void ASwarm::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool ASwarm::CheckSuccess()
{
	isSuccess = player->GetSwarmReaction();
	return isSuccess;
}

void ASwarm::Failed()
{
	UE_LOG(LogTemp, Log, TEXT("FAILED"));
	player->SetPlayerSpeed(slowSpeed);
	player->AddPlayerLives(-1);
}
