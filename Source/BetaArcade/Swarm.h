// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BetaArcadeCharacter.h"
#include "Swarm.generated.h"

UCLASS()
class BETAARCADE_API ASwarm : public AActor
{	
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite)
	ABetaArcadeCharacter* player;

	UPROPERTY(BlueprintReadWrite)
	FKey qteKey;
	FString qteText;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float slowTime = 0.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float slowSpeed = 0.0f;

	UPROPERTY(BlueprintReadWrite)
	bool isSuccess = false;
	
public:	
	// Sets default values for this actor's properties
	ASwarm();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
		void ChooseKey();
	UFUNCTION(BlueprintCallable)
	bool CheckSuccess();
	UFUNCTION(BlueprintCallable)
	void Failed();
	UFUNCTION(BlueprintCallable)
	void ResetPlayer() { player->ResetPlayerSpeed(); };

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
