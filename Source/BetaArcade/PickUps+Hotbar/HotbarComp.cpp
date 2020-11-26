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

	// if giving default items at start of game, uncomment below.

	//for (auto& PickUp : DefaultPickUps)
	//{
	//	AddPickUp(PickUp);
	//}

	
	
}

bool UHotbarComp::AddPickUp(APickUpBase* PickUp)
{
	
	if (PickUps.Num() >= NumSlots || !PickUp)
	{
		return false;
	}
	
	
	PickUp->OwningComp = this;
	/*PickUp->World = GetWorld();*/
	PickUps.Add(PickUp);

	OnHotbarUpdated.Broadcast();
	
	return true;
}

bool UHotbarComp::RemovePickUp(APickUpBase* PickUp)
{
	if (PickUp)
	{
		PickUp->OwningComp = nullptr;
		/*PickUp->World = nullptr;*/
		PickUps.RemoveSingle(PickUp);
		OnHotbarUpdated.Broadcast();
		return true;
	}
	return false;
}




