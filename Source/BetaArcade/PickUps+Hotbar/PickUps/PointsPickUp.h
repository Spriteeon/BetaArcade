// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickUps+Hotbar/PickUpBase.h"
#include "PointsPickUp.generated.h"

/**
 * 
 */
UCLASS()
class BETAARCADE_API APointsPickUp : public APickUpBase
{
	GENERATED_BODY()

		APointsPickUp();
public:
	virtual void ItemAction(class ABetaArcadeCharacter* Character) override;
};
