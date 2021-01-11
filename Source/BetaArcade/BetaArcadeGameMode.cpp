// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "BetaArcadeGameMode.h"
//#include "BetaArcadeCharacter.h"
#include "Math.h"
#include "UObject/ConstructorHelpers.h"

ABetaArcadeGameMode::ABetaArcadeGameMode()
{
	// set default pawn class to our Blueprinted character
	/*static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}*/

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

AActor* ABetaArcadeGameMode::SpawnCornerTile(FVector spawnLocation, FRotator spawnRotation)
{

	UWorld* world = GetWorld();
	if (world)
	{
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;

		tileToSpawn = ETileType::eCorner;

		leftRight = FMath::RandRange(0, 9);
		if (leftRight <= 4) //Left
		{
			spawnedTile = world->SpawnActor<AActor>(leftCornerTileClass, spawnLocation, spawnRotation, spawnParams);
			return spawnedTile;
		}
		else //Right
		{
			spawnedTile = world->SpawnActor<AActor>(rightCornerTileClass, spawnLocation, spawnRotation, spawnParams);
			return spawnedTile;
		}
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

AActor* ABetaArcadeGameMode::SpawnRandomTile(FVector spawnLocation, FRotator spawnRotation)
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
			eSpawnedTile = ETileType::eBasic;
			spawnedTile = world->SpawnActor<AActor>(basicTileClass, spawnLocation, spawnRotation, spawnParams);
			spawnedTiles++;
			return spawnedTile;
			break;

		//case ETileType::eRightCorner:
		//	eSpawnedTile = ETileType::eRightCorner;
		//	spawnedTile = world->SpawnActor<AActor>(rightCornerTileClass, spawnLocation, spawnRotation, spawnParams);
		//	/*eSpawnedTile = ETileType::eBasic;
		//	spawnedTile = world->SpawnActor<AActor>(basicTileClass, spawnLocation, spawnRotation, spawnParams);*/
		//	spawnedTiles++;
		//	return spawnedTile;
		//	break;
		//case ETileType::eLeftCorner:
		//	eSpawnedTile = ETileType::eLeftCorner;
		//	spawnedTile = world->SpawnActor<AActor>(leftCornerTileClass, spawnLocation, spawnRotation, spawnParams);
		//	/*eSpawnedTile = ETileType::eBasic;
		//	spawnedTile = world->SpawnActor<AActor>(basicTileClass, spawnLocation, spawnRotation, spawnParams);*/
		//	spawnedTiles++;
		//	return spawnedTile;
		//	break;

		//Obstacles
		case ETileType::eVault:
			eSpawnedTile = ETileType::eVault;
			spawnedTile = world->SpawnActor<AActor>(vaultTileClass, spawnLocation, spawnRotation, spawnParams);
			spawnedTiles++;
			elastObstacleTile = ETileType::eVault;
			currentTiles.Add(spawnedTile);
			return spawnedTile;
			break;
		case ETileType::eSlide:
			eSpawnedTile = ETileType::eSlide;
			spawnedTile = world->SpawnActor<AActor>(slideTileClass, spawnLocation, spawnRotation, spawnParams);
			spawnedTiles++;
			elastObstacleTile = ETileType::eSlide;
			currentTiles.Add(spawnedTile);
			return spawnedTile;
			break;
		case ETileType::eJump:
			eSpawnedTile = ETileType::eJump;
			spawnedTile = world->SpawnActor<AActor>(jumpTileClass, spawnLocation, spawnRotation, spawnParams);
			spawnedTiles++;
			elastObstacleTile = ETileType::eJump;
			currentTiles.Add(spawnedTile);
			return spawnedTile;
			break;
		case ETileType::eSwarm:
			eSpawnedTile = ETileType::eSwarm;
			spawnedTile = world->SpawnActor<AActor>(swarmTileClass, spawnLocation, spawnRotation, spawnParams);
			//eSpawnedTile = ETileType::eBasic;
			//spawnedTile = world->SpawnActor<AActor>(basicTileClass, spawnLocation, spawnRotation, spawnParams);
			spawnedTiles++;
			elastObstacleTile = ETileType::eSwarm;
			currentTiles.Add(spawnedTile);
			return spawnedTile;
			break;
		case ETileType::eCliff:
			eSpawnedTile = ETileType::eCliff;
			cliffRand = FMath::RandRange(0, 9);
			if (cliffRand <= 4) // Left
			{
				spawnedTile = world->SpawnActor<AActor>(leftCliffTileClass, spawnLocation, spawnRotation, spawnParams);
				spawnedTiles++;
			}
			else // Right
			{
				spawnedTile = world->SpawnActor<AActor>(rightCliffTileClass, spawnLocation, spawnRotation, spawnParams);
				spawnedTiles++;
			}
			currentTiles.Add(spawnedTile);
			elastObstacleTile = ETileType::eCliff;
			return spawnedTile;
			break;
		default:
			return NULL;
			break;
		}
	}
	return NULL;
}

void ABetaArcadeGameMode::ClearTileArray()
{
	currentTiles.Empty();
}

ETileType ABetaArcadeGameMode::GetNextTileType()
{
	if (tileToSpawn == ETileType::eBasic || tileToSpawn == ETileType::eCorner)
	{
		obstacleSpawn = FMath::RandRange(0, 99);
		if (obstacleSpawn <= 50)
		{
			//Spawn an Obstacle Tile
			randomModule = FMath::RandRange(1, 9);
			if (randomModule > 5)
			{
				duplicateTest = randomModule - 5;
			}
			else
			{
				duplicateTest = randomModule;
			}
			if (elastObstacleTile == ETileType(duplicateTest)) //To never get the same obstacle twice in a row
			{
				randomModule++;
				if (randomModule > 9)
				{
					randomModule = 1;
				}
			}

			if (randomModule == 1 || randomModule == 6) // Vault
			{
				return ETileType::eVault;
			}
			else if (randomModule == 2 || randomModule == 7) // Slide
			{
				return ETileType::eSlide;
			}
			else if (randomModule == 3 || randomModule == 8) // Jump
			{
				return ETileType::eJump;
			}
			else if (randomModule == 4 || randomModule == 9) // Cliff
			{
				return ETileType::eCliff;
			}
			else if (randomModule == 5) // Swarm
			{
				return ETileType::eSwarm;
			}
			else
			{
				//ERROR
				return ETileType::eBasic;
			}

			//switch (randomModule)
			//{
			//case 1: //Vault
			//	return ETileType::eVault;
			//	break;
			//case 2: //Slide
			//	return ETileType::eSlide;
			//	break;
			//case 3: //Jump
			//	return ETileType::eJump;
			//	break;
			//case 4: //Cliff
			//	return ETileType::eCliff;
			//	break;
			//case 5: //Swarm
			//	return ETileType::eSwarm;
			//	break;
			//default:
			//	//ERROR
			//	return ETileType::eBasic;
			//	break;
			//}
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
