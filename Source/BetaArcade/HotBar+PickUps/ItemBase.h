// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemBase.generated.h"

UCLASS(Abstract, BlueprintType, Blueprintable, DefaultToInstanced)
class BETAARCADE_API AItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemBase();

	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	
	
	

	
protected:
	
	//Property for pick up mesh.
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* PickUpMesh;

	//Property for pick up thumbnail.
	UPROPERTY(EditAnywhere, Category = "PickUp Properties")
		UTexture2D* PickUpThumbnail;

	//Property for pick up name.
	UPROPERTY(EditAnywhere, Category = "PickUp Properties")
		FString PickUpName;

	//Property for pick up owner.
	UPROPERTY()
		class UHotBarComponent* PickUpOwner;
protected:
	
	//Functions for Item Action (what happens as soon as player interacts with pick up).
	/*C++*/ virtual void ItemActionCPP(class ABetaArcadeCharacter* Character) PURE_VIRTUAL(AItemBase, );
	
	/*BP*/ UFUNCTION(BlueprintImplementableEvent)
			 void ItemActionBP(class ABetaArcadeCharacter* Character);

	//Functions for Hot Bar use (what happens when the item is used from the hot bar).
	/*C++*/ virtual void OnHotbarUseCPP(class ABetaArcadeCharacter* Character) PURE_VIRTUAL(AItemBase, );
	/*BP*/ UFUNCTION(BlueprintImplementableEvent)
			void OnHotbarUseBP(class ABetaArcadeCharacter* Character);

};
