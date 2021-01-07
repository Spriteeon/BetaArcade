// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickUpBase.generated.h"


UCLASS(Abstract, BlueprintType, Blueprintable, DefaultToInstanced)
class BETAARCADE_API APickUpBase : public AActor
{
	GENERATED_BODY()
	

public:	
	// Sets default values for this actor's properties
	APickUpBase();

	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PickUp Properties")
		class UTexture2D* Thumbnail;
protected:


public:	
	/*class ABetaArcadeCharacter;*/

	virtual void ItemAction(class ABetaArcadeCharacter* Character) {};

	/*UFUNCTION(BlueprintCallable)
	virtual void UseFromHotbar(class ABetaArcadeCharacter* Character) {};*/

	
	/*UFUNCTION()
		virtual void DuringTimer(class ABetaArcadeCharacter* Character);*/

	/*bool timerHasBeenCalled;*/
	
	//FTimerManager PickUpTimerHandle;

	/*UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void UseFromHotbarBP(class ABetaArcadeCharacter* Character);*/

	//bool hasBeenAddedToHotbar = true;

	/*UPROPERTY()
		class UHotbarComp* OwningComp;*/

	UPROPERTY(VisibleAnywhere)
		int PickUpID = 0;
	
	UPROPERTY(EditAnywhere)
		int pointsValue = 0;
	

};
