// Fill out your copyright notice in the Description page of Project Settings.


#include "BigScoreMultiplier.h"
#include "BetaArcadeCharacter.h"
#include "PickUps+Hotbar/HotbarComp.h"

ABigScoreMultiplier::ABigScoreMultiplier()
{
	PickUpID = 1;
	pointsValue = 50;
}

void ABigScoreMultiplier::UseFromHotbar(ABetaArcadeCharacter* Character)
{
	if (Character != NULL)
	{

		Character->scoreMultiplier = 5;
		
		Character->Hotbar->RemovePickUp(this);
	}
}

