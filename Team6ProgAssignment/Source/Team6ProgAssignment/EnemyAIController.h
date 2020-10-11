#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

//Forward Declaration
class AAIEnemy;

UCLASS()
class TEAM6PROGASSIGNMENT_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

};
