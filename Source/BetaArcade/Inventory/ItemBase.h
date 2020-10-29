// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BetaArcadeCharacter.h"
#include "ItemBase.generated.h"

UCLASS()
class BETAARCADE_API AItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemBase();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
	
	
	
	//Use function for item.
	UFUNCTION(Category = "Item")
		virtual void OnUse(class ABetaArcadeCharacter* Character)/*PURE_VIRTUAL(AItemBase,)*/ {};

	//Collision function. 
	UFUNCTION(Category = "Item")
		void OnOverlap(AActor* MyOverlappedActor, AActor* OtherActor);

	//Action function (what happens before actor is destroyed).
	UFUNCTION(Category = "Item")
		virtual void ItemAction(ABetaArcadeCharacter* Character, AActor* OtherActor) {};


	
	
	
	
	//Property for item ID number.
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
			int ItemID;

	//Property for item mesh. 
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
			class UStaticMeshComponent* ItemMesh;

	//Property for item Thumbnail. 
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
			class UTexture2D* ItemThumbnail;

	//Property For item name.
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
			FText ItemName;
	
	//Property for collision component.
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
			UCapsuleComponent* PickUpCollision;

	//Hotbar that owns the items. 
		UPROPERTY()
		class UHotBarComponent* OwningHotBar;
	

};
