#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "RunningEnemy.generated.h"

UCLASS()
class BETAARCADE_API ARunningEnemy : public AEnemyBase
{

	GENERATED_BODY()

public:

	ARunningEnemy();

protected:

	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;

	virtual void UpdatePosition() override;
	virtual void Attack() override;
	virtual void Die() override;

};
