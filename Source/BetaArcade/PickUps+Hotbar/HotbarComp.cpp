// Fill out your copyright notice in the Description page of Project Settings.


#include "HotbarComp.h"
#include "PickUpBase.h"


// Sets default values for this component's properties
UHotbarComp::UHotbarComp()
{
}


// Called when the game starts
void UHotbarComp::BeginPlay()
{
	Super::BeginPlay();
	/*PickUp->OwningComp = this;*/
}


bool UHotbarComp::AddPickUp(class APickUpBase* PickUp)
{
	if (PickUps.Num() >= NumSlots || !PickUp)
	{
		/*for(int i = 0; i < PickUps.Size; i++)
			
			if (PickUps[i] = PickUp)
			{
				return false;
			}*/
		
		return false;
	}
	else
	{
		PickUps.Add(PickUp);
		OnHotbarUpdated.Broadcast();

		return true;
	}
}

void UHotbarComp::RemovePickUp(class APickUpBase* PickUp)
{
		PickUps.RemoveSingle(PickUp);
		OnHotbarUpdated.Broadcast();
}














