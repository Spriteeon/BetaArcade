// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtraLifePickUp.h"
#include "BetaArcadeCharacter.h"


AExtraLifePickUp::AExtraLifePickUp()
{
	////ItemID = 12;
	//////UStaticMeshComponent* ItemMesh  = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("XtraLifeMesh"));
	//////PickUpCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("XtraLifeCollision"));
	///////*UCapsuleComponent* PickUpCollision->InitCapsuleExtent(FVector(50.0f, 50.0f, 50.0f));*/
	/////*RootComponent = ItemMesh;*/
	////ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ExtraLifeMesh"));
	/////*AExtraLifePickUp::ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ExtraLifeMesh"));*/
	////this->SetRootComponent(ItemMesh);
}

void AExtraLifePickUp::ItemAction(ABetaArcadeCharacter* Character, AActor* OtherActor)
{
	/*class ABetaArcadeCharacter* Character = Cast<ABetaArcadeCharacter>(OtherActor);*/

	if (Character && Character->GetPlayerLives() < 3)
	{
		Character->AddPlayerLives(1);
		Destroy();
	}
}