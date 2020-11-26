// Fill out your copyright notice in the Description page of Project Settings.


#include "SpeedBoost.h"
#include "BetaArcadeCharacter.h"


ASpeedBoost::ASpeedBoost()
{

}


void ASpeedBoost::ItemAction(class ABetaArcadeCharacter* Character)
{
	
	if (Character != NULL)
	{
		Character->SetPlayerSpeed(10000);

		UE_LOG(LogTemp, Log, TEXT("Speed boost active"));
		/*Destroy();*/
	}
}