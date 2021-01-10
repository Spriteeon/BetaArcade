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

	
	//Thumbnail Property for pick ups.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PickUp Properties")
		class UTexture2D* Thumbnail;
protected:


public:	

	//What happens if the pick up effect is instant (doesnt go into hotbar).
	virtual void ItemAction(class ABetaArcadeCharacter* Character) {};

	//Individual pick up ID used for sorting and using pick ups.
	UPROPERTY(EditAnywhere)
		int PickUpID = 0;

	UPROPERTY(EditAnywhere)
		int pointsValue = 0;

	/*UFUNCTION(BlueprintCallable)
	virtual void UseFromHotbar(class ABetaArcadeCharacter* Character) {};*/

	/*UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void UseFromHotbarBP(class ABetaArcadeCharacter* Character);*/

	//bool hasBeenAddedToHotbar = true;


	
	

};
