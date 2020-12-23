// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickUps+Hotbar/PickUpBase.h"
#include "ExtraLife.generated.h"

/**
 * 
 */
UCLASS()
class BETAARCADE_API AExtraLife : public APickUpBase
{
	GENERATED_BODY()

public:
		AExtraLife();


	
	virtual void ItemAction(class ABetaArcadeCharacter* Character) override;
};
