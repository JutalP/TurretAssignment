#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AIEnemy.generated.h"

//Forward Declaration
class AActor;
//class AAIController;

UCLASS()
class TEAM6PROGASSIGNMENT_API AAIEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	AAIEnemy();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "State")
		bool bPatrol = true;

	void MoveToNextPatrolPoint();

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Movement", meta = (EditCondition = "bPatrol"))
	TArray<AActor*> patrolPoints;

	AActor* currentPatrolPoint = nullptr; 
};