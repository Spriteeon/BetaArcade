// Fill out your copyright notice in the Description page of Project Settings.


#include "ExtraLifePickUp.h"
#include "BetaArcadeCharacter.h"

AExtraLifePickUp::AExtraLifePickUp()
{
	PickUpMesh  = CreateDefaultSubobject<UStaticMeshComponent>(FName("PickUpMesh"));
	
}

void AExtraLifePickUp::ItemActionCPP(class ABetaArcadeCharacter* Character)
{
	if (Character && Character->GetPlayerLives() < 3)
	{
		Character->AddPlayerLives(1);
		Destroy();
	}
}

