// Fill out your copyright notice in the Description page of Project Settings.

#include "AINode.h"

// Sets default values
AAINode::AAINode()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAINode::BeginPlay()
{

	Super::BeginPlay();
	nodePosition = this->GetActorLocation();
	
}

// Called every frame
void AAINode::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);

}

