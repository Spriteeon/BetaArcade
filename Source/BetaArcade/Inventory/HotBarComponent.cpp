// Fill out your copyright notice in the Description page of Project Settings.
//
//#include "HotBarComponent.h"
//#include "ItemBase.h"
//
//// Sets default values for this component's properties
//UHotBarComponent::UHotBarComponent()
//{
//	NumSlots = 5;
//}
//
//
//// Called when the game starts
//void UHotBarComponent::BeginPlay()
//{
//	Super::BeginPlay();
//
//
//	//Uncomment code below when wanting to provide player with items at the start of the game.
//
//	/*for (auto& Item : DefaultItems)
//	{
//		AddItem(Item);
//	}*/
//	 
//}
//
//
////Boolean for adding items to hotbar.
//bool UHotBarComponent::AddItem(class AItemBase* Item)
//{
//
//	//If hotbar is at capacity or item is null, do not add to hotbar. 
//	if (Items.Num() >= NumSlots || !Item)
//	{
//		UE_LOG(LogTemp, Log, TEXT("Failed to add item to HB"));
//		return false;
//	}
//
//
//	Item->OwningHotbar = this;
//	Item->World = GetWorld();
//	Items.Add(Item);
//
//	//Update UI
//	OnHotbarUpdated.Broadcast();
//
//	//If no 'fail to add' conditions are met.
//	UE_LOG(LogTemp, Log, TEXT("Successfully added item to HB"));
//	return true;
//}
//
////Boolean for removing item from hotbar once consumed. 
//bool UHotBarComponent::RemoveItem(AItemBase* Item)
//{
//	if (Item)
//	{
//		Item->OwningHotbar = nullptr;
//		Item->World = nullptr;
//		Items.RemoveSingle(Item);
//		OnHotbarUpdated.Broadcast();
//		return true;
//	}
//
//	return false;
//}
//
//
