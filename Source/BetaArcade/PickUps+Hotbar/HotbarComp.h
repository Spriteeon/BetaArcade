// Fill out your copyright notice in the Description page of Project Settings.

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
	virtual void BeginPlay() override;

	bool AddPickUp(class APickUpBase* PickUp);
	bool RemovePickUp(class APickUpBase* PickUp);

	UPROPERTY(EditAnywhere, Instanced)
	TArray<class APickUpBase*> DefaultPickUps;

	UPROPERTY(EditAnywhere)
		int32 NumSlots = 0;

	UPROPERTY(BlueprintAssignable)
	FOnHotbarUpdated OnHotbarUpdated;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<class APickUpBase*> PickUps;


	

		
};
