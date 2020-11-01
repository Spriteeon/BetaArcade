// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtraLifePickUp.h"
#include "BetaArcadeCharacter.h"


AExtraLifePickUp::AExtraLifePickUp()
{
	ItemID = 0;
	
	/* ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("XtraLifeMesh1"));
	PickUpCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("XtraLifeCollision1"));*/
	/*PickUpCollision = InitCapsuleSize()*/
	/////*RootComponent = ItemMesh;*/
	////ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ExtraLifeMesh"));
	/////*AExtraLifePickUp::ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ExtraLifeMesh"));*/
	////this->SetRootComponent(ItemMesh);
}

void AExtraLifePickUp::ItemAction(class ABetaArcadeCharacter* Character)
{
		if (Character && Character->GetPlayerLives() < 3)
		{
				Character->AddPlayerLives(1);
				Destroy();
		}
}
