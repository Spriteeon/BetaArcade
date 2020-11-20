// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "BetaArcadeGameMode.h"
#include "BetaArcadeCharacter.h"
#include "Math.h"
#include "UObject/ConstructorHelpers.h"

ABetaArcadeGameMode::ABetaArcadeGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	spawnedTiles = 0;

}

AActor* ABetaArcadeGameMode::SpawnStartTile()
{
	
	UWorld* world = GetWorld();
	if (world)
	{
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;

		spawnedTile = world->SpawnActor<AActor>(basicTileClass, nextTileLocation, nextTileRotation, spawnParams);
		return spawnedTile;
	}
	return NULL;
}

AActor* ABetaArcadeGameMode::SetTileTransform(AActor* tile)
{

	tile->SetActorLocationAndRotation(nextTileLocation, nextTileRotation);
	//tile->SetActorLocation(nextTileLocation);
	//tile->SetActorRotation(nextTileRotation);

	return tile;

}

void ABetaArcadeGameMode::SetNewTransforms(FVector nextLocation, FRotator nextRotation)
{

	nextTileLocation = nextLocation;
	nextTileRotation = nextRotation;

}

AActor* ABetaArcadeGameMode::SpawnNewTile(FVector spawnLocation, FRotator spawnRotation)
{

	UWorld* world = GetWorld();
	if (world)
	{
		tileToSpawn = GetNextTileType();
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;

		if (tileToSpawn == ETileType::eBasic)
		{
			spawnedTile = world->SpawnActor<AActor>(basicTileClass, spawnLocation, spawnRotation, spawnParams);
			spawnedTiles++;
			return spawnedTile;
		}
		else if (tileToSpawn == ETileType::eRightCorner)
		{
			spawnedTile = world->SpawnActor<AActor>(rightCornerTileClass, spawnLocation, spawnRotation, spawnParams);
			spawnedTiles++;
			return spawnedTile;
		}
		else if (tileToSpawn == ETileType::eLeftCorner)
		{
			spawnedTile = world->SpawnActor<AActor>(leftCornerTileClass, spawnLocation, spawnRotation, spawnParams);
			spawnedTiles++;
			return spawnedTile;
		}
		else if (tileToSpawn == ETileType::eJump)
		{
			spawnedTile = world->SpawnActor<AActor>(jumpTileClass, spawnLocation, spawnRotation, spawnParams);
			spawnedTiles++;
			return spawnedTile;
		}
		else
		{
			return NULL;
		}
	}
	return NULL;
}

ETileType ABetaArcadeGameMode::GetNextTileType()
{
	if (spawnedTiles % 10 == 0) //Every 10 Tiles
	{
		leftRight = FMath::RandRange(0, 9);
		if (leftRight <= 4) //Left
		{
			return ETileType::eLeftCorner;
		}
		else //Right
		{
			return ETileType::eRightCorner;
		}
	}
	else if (spawnedTiles % 2 == 0) //Every 2 Tiles not including the 10th
	{
		return ETileType::eJump;
	}
	else
	{
		return ETileType::eBasic;
	}
}
