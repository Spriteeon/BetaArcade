// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickUps+Hotbar/PickUpBase.h"
#include "LightOrb.generated.h"

/**
 * 
 */
UCLASS()
class BETAARCADE_API ALightOrb : public APickUpBase
{
	GENERATED_BODY()

public:
	ALightOrb();

protected:

public:


	virtual void ItemAction(class ABetaArcadeCharacter* Character) override;

	/*UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void SetMagnetCollisionOn();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void SetStandardCollisionOn();*/
};
