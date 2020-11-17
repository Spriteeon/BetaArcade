// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HotBar+PickUps/ItemBase.h"
#include "ExtraLifePickUp.generated.h"

/**
 * 
 */
UCLASS()
class BETAARCADE_API AExtraLifePickUp : public AItemBase
{
	GENERATED_BODY()

protected:
	virtual void ItemActionCPP(class ABetaArcadeCharacter* Character) override;

public:
	AExtraLifePickUp();
	
};
