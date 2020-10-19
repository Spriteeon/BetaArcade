// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerCharacterState.generated.h"

/**
 * 
 */
UCLASS()
class BETAARCADE_API APlayerCharacterState : public APlayerController
{
	GENERATED_BODY()

public:
	// virtual ~APlayerCharacterState() {} // - Do I need a deconstructor in unreal?
	virtual void HandleInput() {}
};
