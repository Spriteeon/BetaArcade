#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyBase.generated.h"

UCLASS()
class BETAARCADE_API AEnemyBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyBase();

protected:

public:	

	int health{ 0 };
	int points{ 0 };
	float speed{ 0.0f };

	virtual void UpdatePosition() {};
	virtual void Attack() {};
	virtual void Die() {};

};
