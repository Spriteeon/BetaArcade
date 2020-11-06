// Fill out your copyright notice in the Description page of Project Settings.

#include "AIPoint.h"
#include "Components/SphereComponent.h"

// Sets default values
AAIPoint::AAIPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	pointCollison = CreateDefaultSubobject<USphereComponent>(TEXT("Collisions"));
	pointCollison->InitSphereRadius(50.0f);

}

// Called when the game starts or when spawned
void AAIPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAIPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

