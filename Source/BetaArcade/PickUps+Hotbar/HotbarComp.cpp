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

//Determins which power up function is called. 
void UHotbarComp::HandleHotbar(int ID)
{
	switch (ID)
	{
		case 1:
			SpeedBoostAction();
			RemovePickUp(1);
			break;

		case 2:
			BigScoreMultiplierAction();
			RemovePickUp(2);
			break;

		case 3:
			MagnetAction();
			RemovePickUp(3);
			break;

		case 4:
			SecondWindAction();
			RemovePickUp(4);
			break;
	}
		
}


//Speed boost effect
void UHotbarComp::SpeedBoostAction()
{
	if (Character != NULL)
	{
		Character->SetPlayerSpeed(6500);
		Character->scoreMultiplier = 2;
		Character->currentPowerState = PowerState::State::SpeedBoost;
		
	}
}

//Score multiplier effect
void UHotbarComp::BigScoreMultiplierAction()
{
	if (Character != NULL)
	{
		Character->currentPowerState = PowerState::State::ScoreBonus;
		Character->scoreMultiplier = 5;
		
	}
}

//Second wind effect
void UHotbarComp::SecondWindAction()
{
	if (Character != NULL && Character->GetPlayerLives() <= 0 && PickUpIDs.Contains(10))
	{
		Character->currentPowerState = PowerState::State::SecondWind;
		Character->AddPlayerLives(1);
		
		RemovePickUp(4);
	}
}

//Magnet effect (changes isMagnetActive which calls blueprint function to switch orb collision)
void UHotbarComp::MagnetAction()
{
	if (Character != NULL)
	{
		Character->currentPowerState = PowerState::State::Magnet;
		Character->isMagnetActive = true;
		UE_LOG(LogTemp, Log, TEXT("Magnet true"));

		RemovePickUp(3);
	}
	
}

//Add PickUp to hotbar
bool UHotbarComp::AddPickUp(class APickUpBase* PickUp)
{

	//Checks to see if pick up of that type is already in hotbar.
	for(int i = 0; i < PickUpIDs.Num(); ++i)
	{
		if (PickUpIDs.Contains(PickUp->PickUpID))
		{
			UE_LOG(LogTemp, Log, TEXT("Already got one!"));  
			return true;
			
		}
	}
	
	
	//If pick up is not already in hotbar, checks to see if there is an available slot.
	if (PickUpIDs.Num() >= NumSlots || !PickUp)
	{
		//if no slot is available
		UE_LOG(LogTemp, Log, TEXT("Hotbar Full!"));
		return false;
	}
	else
	{
		//if slot available
		PickUpIDs.Add(PickUp->PickUpID);
		OnHotbarUpdated.Broadcast();

		return true;
	}
}

//Remove pick up from hotbar
void UHotbarComp::RemovePickUp(int ID)
{
	PickUpIDs.RemoveSingle(ID);
	OnHotbarUpdated.Broadcast();
}















