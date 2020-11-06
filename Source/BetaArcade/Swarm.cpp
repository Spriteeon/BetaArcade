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

// Called every frame
void ASwarm::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (inArea)
	{
		if (!isSuccess) // Player hasn't pressed button yet
		{
			UE_LOG(LogTemp, Log, TEXT("SWARM ATTACK"));
			if (CheckSuccess())
			{
				UE_LOG(LogTemp, Log, TEXT("SUCCESS"));
			}
		}
	}
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
}
