// Fill out your copyright notice in the Description page of Project Settings.


#include "PointsPickUp.h"
#include "BetaArcadeCharacter.h"


APointsPickUp::APointsPickUp()
{
	PickUpID = 2;
	pointsValue = rand() % 250;
}


void APointsPickUp::ItemAction(class ABetaArcadeCharacter* Character)
{
	if (Character != NULL)
	{
		Character->AddPointsToScore(pointsValue);
		
		/*Destroy();*/
	}
}