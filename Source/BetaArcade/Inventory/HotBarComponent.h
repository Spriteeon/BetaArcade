//// Fill out your copyright notice in the Description page of Project Settings.
////
////#pragma once
////
////#include "CoreMinimal.h"
////#include "Components/ActorComponent.h"
////#include "HotBarComponent.generated.h"
////
////
//////Binding events to UI via Blueprints
////DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHotbarUpdated);
////
////UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
////class BETAARCADE_API UHotBarComponent : public UActorComponent
////{
////	GENERATED_BODY()
////
////public:	
////	// Sets default values for this component's properties
////	UHotBarComponent();
////	
////	// Called when the game starts
////	virtual void BeginPlay() override;
////
////	bool AddItem(class AItemBase* Item);
////	bool RemoveItem(class AItemBase* Item);
////
////
////	//For Items to be given at the start of the game.
////	/*UPROPERTY(EditAnywhere, Instanced)
////		TArray<class AItemBase*> DefaultItems;*/
////
////	//Number of slots in the inventory. 
////	UPROPERTY(EditAnywhere, Category = "Hotbar")
////		int32 NumSlots;
////
////	//UPROPERTY for updating the UI. 
////	UPROPERTY(BlueprintAssignable, Category = "Hotbar")
////		FOnHotbarUpdated OnHotbarUpdated;
////
////	//Array of items currently in hotbar
////	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Items")
////		TArray<class AItemBase*> Items;
////
////
//protected:
//	
//
//
//	
//
//		
//};
