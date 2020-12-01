//// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
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
	TArray<class APickUpBase*> PickUps;
	
	UFUNCTION(BlueprintCallable)
	void UseHotbarItem(class APickUpBase* PickUp);

	/*UHotbarComp* get_this(UHotbarComp)
	{
		return this;
	}*/


	//Add and Remove from hotbar Functions. 
	bool AddPickUp(class APickUpBase* PickUp);
	void RemovePickUp(class APickUpBase* PickUp);

};
