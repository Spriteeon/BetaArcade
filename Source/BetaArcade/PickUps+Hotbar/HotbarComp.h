//// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
//#include "BetaArcadeCharacter.h"
#include "HotbarComp.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHotbarUpdated);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BETAARCADE_API UHotbarComp : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHotbarComp();
	
	// Called when the game starts
	virtual void BeginPlay();

	//Hotbar Capacity.
	UPROPERTY(EditAnywhere)
		int NumSlots = 0;
	
	//Delegate for updating UI.
	UPROPERTY(BlueprintAssignable)
	FOnHotbarUpdated OnHotbarUpdated;

	//PickUp array. 
	UPROPERTY(BlueprintReadOnly)
	TArray<int> PickUpIDs;
	
	/*UPROPERTY(BlueprintReadOnly)
	TArray<UTexture2D*> HBPickUpThumbnails;*/
	
	/*UFUNCTION(BlueprintCallable)
	void UseHotbarItem(class APickUpBase* PickUp);*/

	/*UHotbarComp* get_this(UHotbarComp)
	{
		return this;
	}*/

	UFUNCTION(BlueprintCallable)
	void HandleHotbar(int ID);

	

	void SpeedBoostAction();

	void BigScoreMultiplierAction();

	void SecondWindAction();

	//Add and Remove from hotbar Functions. 
	bool AddPickUp(class APickUpBase* PickUp);
	
	UFUNCTION(BlueprintCallable)
	void RemovePickUp(int ID);

	/*UFUNCTION()
		UTexture2D GetCorrospondingThumbnail(class APickUpBase* PickUp)
	{
		if (PickUp->PickUpID == 1)
		{
			return PickUp->Thumbnail;
		}
	}*/

	UFUNCTION(BlueprintCallable)
		void MagnetAction();

	UPROPERTY(EditAnywhere)
	class ABetaArcadeCharacter* Character;

};