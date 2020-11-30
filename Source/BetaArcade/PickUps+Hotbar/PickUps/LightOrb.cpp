// Fill out your copyright notice in the Description page of Project Settings.


#include "LightOrb.h"
#include "BetaArcadeCharacter.h"

ALightOrb::ALightOrb()
{
	PickUpID = 3;
}


void ALightOrb::ItemAction(class ABetaArcadeCharacter* Character)
{
	if (Character && Character->GetLightAmount() < 150)
	{
		Character->AddLightAmount(10);

		UE_LOG(LogTemp, Log, TEXT("Added light"));
		/*Destroy();*/
	}
}