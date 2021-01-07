// Fill out your copyright notice in the Description page of Project Settings.


#include "SpeedBoost.h"

#include "BetaArcadeCharacter.h"
#include "PickUps+Hotbar/HotbarComp.h"
#include "TimerManager.h"


ASpeedBoost::ASpeedBoost()
{
	PickUpID = 1;
	pointsValue = 100;
	/*Thumbnail = */
}



//void ASpeedBoost::DuringTimer(class ABetaArcadeCharacter* Character)
//{
		
//}

//void ASpeedBoost::UseFromHotbar(class ABetaArcadeCharacter* Character)
//{
//	if (Character != NULL)
//	{
//		Character->SetPlayerSpeed(8000);
//		Character->scoreMultiplier = 2;
//		timerHasBeenCalled = true;
//		UE_LOG(LogTemp, Log, TEXT("Speed boost active"));
//		Character->Hotbar->RemovePickUp(this);
//	}
//	//if (timerHasBeenCalled = true)
//	//{
//		//GetWorldTimerManager().ClearTimer(PickUpTimerHandle);
//	//}
//}