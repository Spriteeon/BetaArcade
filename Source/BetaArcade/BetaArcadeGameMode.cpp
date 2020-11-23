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

		switch (tileToSpawn)
		{
		case ETileType::eBasic:
			spawnedTile = world->SpawnActor<AActor>(basicTileClass, spawnLocation, spawnRotation, spawnParams);
			spawnedTiles++;
			return spawnedTile;
			break;
		case ETileType::eRightCorner:
			spawnedTile = world->SpawnActor<AActor>(rightCornerTileClass, spawnLocation, spawnRotation, spawnParams);
			spawnedTiles++;
			return spawnedTile;
			break;
		case ETileType::eLeftCorner:
			spawnedTile = world->SpawnActor<AActor>(leftCornerTileClass, spawnLocation, spawnRotation, spawnParams);
			spawnedTiles++;
			return spawnedTile;
			break;

		//Obstacles
		case ETileType::eVault:
			spawnedTile = world->SpawnActor<AActor>(vaultTileClass, spawnLocation, spawnRotation, spawnParams);
			spawnedTiles++;
			lastObstacleTile = ETileType::eVault;
			return spawnedTile;
			break;
		case ETileType::eSlide:
			spawnedTile = world->SpawnActor<AActor>(slideTileClass, spawnLocation, spawnRotation, spawnParams);
			spawnedTiles++;
			lastObstacleTile = ETileType::eSlide;
			return spawnedTile;
			break;
		case ETileType::eJump:
			spawnedTile = world->SpawnActor<AActor>(jumpTileClass, spawnLocation, spawnRotation, spawnParams);
			spawnedTiles++;
			lastObstacleTile = ETileType::eJump;
			return spawnedTile;
			break;
		default:
			return NULL;
			break;

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
	else if (tileToSpawn == ETileType::eBasic || tileToSpawn == ETileType::eLeftCorner || tileToSpawn == ETileType::eRightCorner)
	{
		obstacleSpawn = FMath::RandRange(0, 99);
		if (obstacleSpawn <= 49)
		{
			//Spawn an Obstacle Tile
			randomModule = FMath::RandRange(4, 6);
			if (lastObstacleTile == ETileType(randomModule)) //To never get the same obstacle twice in a row
			{
				randomModule++;
				if (randomModule > 6)
				{
					randomModule = 4;
				}
			}
			switch (randomModule)
			{
			case 4: //Vault
				return ETileType::eVault;
				break;
			case 5: //Slide
				return ETileType::eSlide;
				break;
			case 6: //Jump
				return ETileType::eJump;
				break;
			default:
				//ERROR
				return ETileType::eNone;
				break;
			}
		}
		else
		{
			return ETileType::eBasic;
		}
	}
	else
	{
		return ETileType::eBasic;
	}
}
