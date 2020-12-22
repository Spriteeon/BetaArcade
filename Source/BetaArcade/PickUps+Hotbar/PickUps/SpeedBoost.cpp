// Fill out your copyright notice in the Description page of Project Settings.


#include "SpeedBoost.h"
#include "BetaArcadeCharacter.h"
#include "PickUps+Hotbar/HotbarComp.h"



ASpeedBoost::ASpeedBoost()
{
	PickUpID = 1;
	pointsValue = 100;
}


//void ASpeedBoost::ItemAction(class ABetaArcadeCharacter* Character)
//{
//	
//	OwningComp->AddPickUp(this);
//	/*AddPickUp(this);*/
//	/*OwningComp->AddPickUp(this);*/
//		
//			
//			/*UE_LOG(LogTemp, Log, TEXT("PickUpUsed"));*/
//				
//		
//	
//	/*OwningComp->AddPickUp(this);*/
//	//if (Character != NULL)
//	//{
//	//	Character->SetPlayerSpeed(10000);
//
//	//	UE_LOG(LogTemp, Log, TEXT("Speed boost active"));
//	//	/*Destroy();*/
//	//}
//}
void ASpeedBoost::UseFromHotbar(class ABetaArcadeCharacter* Character)
{
	if (Character != NULL)
	{

		Character->SetPlayerSpeed(5000);
		Character->scoreMultiplier = 2;
		UE_LOG(LogTemp, Log, TEXT("Speed boost active"));
		/*Character->AddPointsToScore(++pointsValue);*/
		
		/*Destroy();*/
		Character->Hotbar->RemovePickUp(this);
	}
}