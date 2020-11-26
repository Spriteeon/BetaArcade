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

	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PickUp Properties")
		class UTexture2D* Thumbnail;
protected:


public:	


	virtual void ItemAction(class ABetaArcadeCharacter* Character) {};

	UPROPERTY()
		class UHotbarComp* OwningComp;
	
	
	
	
	
	
	
	
	
	/*virtual class UWorld* GetWorld() const { return World; };

	UPROPERTY(Transient)
		class UWorld* World;*/

};
