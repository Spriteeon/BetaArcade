// Fill out your copyright notice in the Description page of Project Settings.


#include "SpeedBoost.h"
#include "PickUps+Hotbar/HotbarComp.h"
#include "BetaArcadeCharacter.h"


ASpeedBoost::ASpeedBoost()
{

}


void ASpeedBoost::ItemAction(class ABetaArcadeCharacter* Character)
{
	
	OwningComp->AddPickUp(this);
	/*OwningComp->AddPickUp(this);*/
		
			
			/*UE_LOG(LogTemp, Log, TEXT("PickUpUsed"));*/
				
		
	
	/*OwningComp->AddPickUp(this);*/
	//if (Character != NULL)
	//{
	//	Character->SetPlayerSpeed(10000);

	//	UE_LOG(LogTemp, Log, TEXT("Speed boost active"));
	//	/*Destroy();*/
	//}
}