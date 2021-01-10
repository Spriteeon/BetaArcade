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

	//Hotbar slot Capacity.
	UPROPERTY(EditAnywhere)
	int NumSlots = 0;
	
	//Delegate for updating UI.
	UPROPERTY(BlueprintAssignable)
	FOnHotbarUpdated OnHotbarUpdated;

	//PickUps in hotbar array. 
	UPROPERTY(BlueprintReadOnly)
	TArray<int> PickUpIDs;

	//Handles which pick up effect function is called.
	UFUNCTION(BlueprintCallable)
	void HandleHotbar(int ID);

	
	//Pick Up effect functions.
	void SpeedBoostAction();

	void BigScoreMultiplierAction();

	void SecondWindAction();

	UFUNCTION(BlueprintCallable)
	void MagnetAction();


	//Add and Remove from hotbar Functions. 
	bool AddPickUp(class APickUpBase* PickUp);
	
	UFUNCTION(BlueprintCallable)
	void RemovePickUp(int ID);

	//Instance of character to assign hotbar to in editor.
	UPROPERTY(EditAnywhere)
	class ABetaArcadeCharacter* Character;

};