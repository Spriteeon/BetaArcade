// Fill out your copyright notice in the Description page of Project Settings.


#include "HotbarComp.h"
#include "PickUpBase.h"


// Sets default values for this component's properties
UHotbarComp::UHotbarComp()
{
	NumSlots = 5;
}


// Called when the game starts
void UHotbarComp::BeginPlay()
{
	Super::BeginPlay();
	/*PickUp->OwningComp = this;*/
}

void UHotbarComp::UseHotbarItem(class APickUpBase* PickUp)
{
	
}

bool UHotbarComp::AddPickUp(class APickUpBase* PickUp)
{
	
	/*TSharedPtr<class UHotbarComp> MysharedPointer = mysharedReference;*/
	/*this->GetOwner();*/
	/*if(this->GetOwner() == !NULL)*/
	/*AActor* test = this->GetOwner();*/

	PickUps.Add(PickUp);
	PickUp->SetActorHiddenInGame(true);
	
	/*for (APickUpBase* PickUp : PickUps)
	{
		UE_LOG(LogTemp, Log, TEXT("PickUp: %s"), *PickUp->GetName());
		
	}*/
	return false;

	//Update UI.
	OnHotbarUpdated.Broadcast();
}

void UHotbarComp::RemovePickUp(class APickUpBase* PickUp)
{
	PickUps.Remove(PickUp);
}














