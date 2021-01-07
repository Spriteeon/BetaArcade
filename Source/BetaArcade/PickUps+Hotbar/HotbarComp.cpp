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
	
}

//Add PickUp to hotbar
bool UHotbarComp::AddPickUp(class APickUpBase* PickUp)
{

	//Checks to see if pick up of that type is already in hotbar.
	for(int i = 0; i < PickUps.Num(); ++i)
	{
		//if (PickUps.Contains(PickUp))
		//{
			//UE_LOG(LogTemp, Log, TEXT("Already got one!"));  
			//return true;
			
		//}
	}
	
	
	//If pick up is not already in hotbar, checks to see if there is an available slot.
	if (PickUps.Num() >= NumSlots || !PickUp)
	{
		
		UE_LOG(LogTemp, Log, TEXT("Hotbar Full!"));
		return false;
	}
	else
	{
		PickUps.Add(PickUp);
		OnHotbarUpdated.Broadcast();

		return true;
	}
}

//Remove pick up from hotbar
void UHotbarComp::RemovePickUp(class APickUpBase* PickUp)
{
		PickUps.RemoveSingle(PickUp);
		OnHotbarUpdated.Broadcast();
}














