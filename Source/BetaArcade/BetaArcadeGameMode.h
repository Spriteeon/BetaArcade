// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BetaArcadeGameMode.generated.h"

UCLASS(minimalapi)
class ABetaArcadeGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	ABetaArcadeGameMode();

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Transform)
	FTransform nextTileTransform;*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Tile)
		const TSubclassOf<class AActor> tileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Tile)
		AActor* newTile;

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

};



