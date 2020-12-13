// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Math.h"
#include "BetaArcadeGameMode.generated.h"

UENUM(BlueprintType)
enum class ETileType : uint8
{
	eBasic,
	eRightCorner,
	eLeftCorner,
	eVault,
	eSlide,
	eJump,
	eRightCliff,
	eLeftCliff,
	
};

UCLASS(minimalapi)
class ABetaArcadeGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	ABetaArcadeGameMode();

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Transform)
	FTransform nextTileTransform;*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Tile)
		ETileType tileToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Tile)
		TSubclassOf<class AActor> basicTileClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Tile)
		TSubclassOf<class AActor> rightCornerTileClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Tile)
		TSubclassOf<class AActor> leftCornerTileClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Tile)
		TSubclassOf<class AActor> jumpTileClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Tile)
		TSubclassOf<class AActor> slideTileClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Tile)
		TSubclassOf<class AActor> vaultTileClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Tile)
		TSubclassOf<class AActor> leftCliffTileClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Tile)
		TSubclassOf<class AActor> rightCliffTileClass;

	int leftRight;
	int randomModule;
	int obstacleSpawn;

	
	AActor* spawnedTile;
	ETileType lastObstacleTile = ETileType::eBasic;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	ETileType eSpawnedTile = ETileType::eBasic;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TileTransform)
		FVector nextTileLocation = { 0.0f, 0.0f, 0.0f };
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TileTransform)
		FRotator nextTileRotation = { 0.0f, 0.0f, 0.0f };

	UFUNCTION(BlueprintCallable)
		AActor* SpawnStartTile();

	UFUNCTION(BlueprintCallable)
		AActor* SetTileTransform(AActor* tile);

	UFUNCTION(BlueprintCallable)
		void SetNewTransforms(FVector nextLocation, FRotator nextRotation);

	UFUNCTION(BlueprintCallable)
		AActor* SpawnNewTile(FVector spawnLocation, FRotator spawnRotation);

	ETileType GetNextTileType();
	int spawnedTiles;
	int cliffRand;

};



