// Fill out your copyright notice in the Description page of Project Settings.


#include "ExtraLife.h"
#include "BetaArcadeCharacter.h"




AExtraLife::AExtraLife()
{
	PickUpID = 6;
	pointsValue = 30;
}


void AExtraLife::ItemAction(class ABetaArcadeCharacter* Character)
{
	if (Character && Character->GetPlayerLives() < 3)
	{
		Character->AddPlayerLives(1);
		Character->AddPointsToScore(pointsValue);
		UE_LOG(LogTemp, Log, TEXT("Added life"));
		/*Destroy();*/
	}
}
