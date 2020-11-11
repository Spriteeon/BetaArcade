// Fill out your copyright notice in the Description page of Project Settings.

//#pragma once
//
//#include "CoreMinimal.h"
//#include "GameFramework/Actor.h"
//#include "BetaArcadeCharacter.h"
//#include "Components/CapsuleComponent.h"
//#include "ItemBase.generated.h"
//
//UCLASS(Abstract)
//class BETAARCADE_API AItemBase : public AActor
//{
//	GENERATED_BODY()
//	
//public:	
//	// Sets default values for this actor's properties
//	AItemBase();
//	
//	virtual class UWorld* GetWorld() const { return World; };
//	
//	// Called every frame
//	virtual void Tick(float DeltaTime) override;
//
//	// Called when the game starts or when spawned
//	virtual void BeginPlay() override;
//
//	
//	
//	
//	
//	//Use function for item.
//	UFUNCTION(Category = "Item")
//		virtual void OnHotbarUse(class ABetaArcadeCharacter* Character)PURE_VIRTUAL(AItemBase, );
//
//	//Collision function. 
//	UFUNCTION(Category = "Item")
//		void OnOverlap(AActor* MyOverlappedActor, AActor* OtherActor);
//
//	//Action function (what happens before actor is destroyed).
//	UFUNCTION(Category = "Item")
//		virtual void ItemAction(ABetaArcadeCharacter* Character) PURE_VIRTUAL(AItemBase, );
//	
//	UFUNCTION(/*BlueprintImplementableEvent,*/ Category = "Item")
//		void ItemActionBP(class ABetaArcadeCharacter* Character) {}; //Blueprint Event Function. 
//
//	
//	
//	
//	//Item property to tell items what world they are in.
//		UPROPERTY(Transient)
//		class UWorld* World;
//
//	//Item property for item ID number.
//		UPROPERTY(VisibleAnywhere, /*BlueprintReadOnly,*/ Category = "Item")
//			int ItemID;
//
//	//Item property for item mesh. 
//		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
//			class UStaticMeshComponent* ItemMesh;
//
//
//	//Item property for item Thumbnail. 
//		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
//			class UTexture2D* ItemThumbnail;
//
//	//Item property For item name.
//		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
//			FText ItemName;
//	
//	//Item property for collision component.
//		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
//			UCapsuleComponent* PickUpCollision;
//		
//	
//
//	//Hotbar that 'owns' the items. 
//		UPROPERTY()
//		class UHotBarComponent* OwningHotbar;
//	
//
//
//};
