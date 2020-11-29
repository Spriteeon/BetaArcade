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
	
	
	UPROPERTY(VisibleAnywhere)
	TArray<class APickUpBase*> PickUps;
	
	
	// Called when the game starts
	virtual void BeginPlay() override;


	

	

	

	/*UPROPERTY(EditAnywhere)
		int NumSlots = 0;*/

	UPROPERTY(BlueprintAssignable)
	FOnHotbarUpdated OnHotbarUpdated;

	bool AddPickUp(class APickUpBase* Item);
	void RemovePickUp(class ApickUpBase* Item);

	
	

		
};
