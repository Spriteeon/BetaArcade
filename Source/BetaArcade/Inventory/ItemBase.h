// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//#include "Engine.h"
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
		virtual void OnUse(class ABetaArcadeCharacter* Character)PURE_VIRTUAL(AItemBase,);

	//Collision function. 
	UFUNCTION(Category = "Item")
		void OnOverlap(AActor* MyOverlappedActor, AActor* OtherActor);
		
	//Property for item ID number.
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
			int ItemID;

	//Property for item mesh. 
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
			class UStaticMesh* ItemMesh;

	//Property for item Thumbnail. 
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
			class UTexture2D* ItemThumbnail;

	//Property For item name.
		UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Item")
			FText ItemName;

	//Hotbar that owns the items. 
		UPROPERTY()
		class UHotBarComponent* OwningHotBar;
	

};
