// Fill out your copyright notice in the Description page of Project Settings.


#include "HotbarComp.h"
#include "PickUpBase.h"

// Sets default values for this component's properties
UHotbarComp::UHotbarComp()
{
	/*NumSlots = 5;*/
}


// Called when the game starts
void UHotbarComp::BeginPlay()
{
	Super::BeginPlay();

	// if giving default items at start of game, uncomment below.

	//for (auto& PickUp : DefaultPickUps)
	//{
	//	AddPickUp(PickUp);
	//}

	
	
}

bool UHotbarComp::AddPickUp(APickUpBase* Item)
{
	PickUps.Add(Item);
	for (APickUpBase* PickUp : PickUps)
	{
		UE_LOG(LogTemp, Log, TEXT("PickUp: %s"), *PickUp->GetName());
		
	}
	return false;

	OnHotbarUpdated.Broadcast();
}














