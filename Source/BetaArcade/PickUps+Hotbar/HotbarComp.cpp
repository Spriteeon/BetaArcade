// Fill out your copyright notice in the Description page of Project Settings.


#include "HotbarComp.h"
#include "PickUpBase.h"
#include "BetaArcadeCharacter.h"
#include "PickUps/SpeedBoost.h"
#include "PickUps/Magnet.h"
#include "PickUps/BigScoreMultiplier.h"




// Sets default values for this component's properties
UHotbarComp::UHotbarComp()
{

}


// Called when the game starts
void UHotbarComp::BeginPlay()
{
	Super::BeginPlay();
	
}

void UHotbarComp::HandleHotbar(int ID)
{
	switch (ID)
	{
		case 1:
			SpeedBoostAction();
			break;

		case 2:
			BigScoreMultiplierAction();
			break;

		case 3:
			MagnetAction();
			break;

	}
		
}



void UHotbarComp::SpeedBoostAction()
{
	if (Character != NULL)
	{
		Character->SetPlayerSpeed(5500);
		Character->scoreMultiplier = 2;
		UE_LOG(LogTemp, Log, TEXT("Speed boost active"));
		//Character->Hotbar->RemovePickUp(PickUp);
	}
}

void UHotbarComp::BigScoreMultiplierAction()
{
	if (Character != NULL)
	{

		Character->scoreMultiplier = 5;

		//RemovePickUp(this);
	}
}

//Add PickUp to hotbar
bool UHotbarComp::AddPickUp(class APickUpBase* PickUp)
{

	//Checks to see if pick up of that type is already in hotbar.
	for(int i = 0; i < PickUpIDs.Num(); ++i)
	{
		//if (PickUps.Contains(PickUp))
		//{
			//UE_LOG(LogTemp, Log, TEXT("Already got one!"));  
			//return true;
			
		//}
	}
	
	
	//If pick up is not already in hotbar, checks to see if there is an available slot.
	if (PickUpIDs.Num() >= NumSlots || !PickUp)
	{
		
		UE_LOG(LogTemp, Log, TEXT("Hotbar Full!"));
		return false;
	}
	else
	{
		PickUpIDs.Add(PickUp->PickUpID);
		//HBPickUpThumbnails.Add(PickUp->Thumbnail);
		OnHotbarUpdated.Broadcast();

		return true;
	}
}

void UHotbarComp::RemovePickUp(int ID)
{
	PickUpIDs.RemoveSingle(ID);
	//HBPickUpThumbnails.RemoveSingle(tn);
	OnHotbarUpdated.Broadcast();
}

////Remove pick up from hotbar
//void UHotbarComp::RemovePickUp(/*class APickUpBase* PickUp*/)
//{
//		PickUpIDs.RemoveSingle(PickUp->PickUpID);
//		OnHotbarUpdated.Broadcast();
//}














