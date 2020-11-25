// Fill out your copyright notice in the Description page of Project Settings.


#include "ExtraLife.h"
#include "BetaArcadeCharacter.h"




AExtraLife::AExtraLife()
{
	
}


void AExtraLife::ItemAction(class ABetaArcadeCharacter* Character)
{
	if (Character && Character->GetPlayerLives() < 5)
	{
		Character->AddPlayerLives(1);

		UE_LOG(LogTemp, Log, TEXT("Added life"));
		/*Destroy();*/
	}
}
