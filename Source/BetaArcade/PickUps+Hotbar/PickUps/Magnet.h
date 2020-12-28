// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickUps+Hotbar/PickUpBase.h"
#include "Magnet.generated.h"

/**
 * 
 */
UCLASS()
class BETAARCADE_API AMagnet : public APickUpBase
{
	GENERATED_BODY()
	
public:
	
	AMagnet();
	
	//virtual void UseFromHotbar(class ABetaArcadeCharacter* Character) override;
};
