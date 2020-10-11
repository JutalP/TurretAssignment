#include "AIEnemy.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Components/SkeletalMeshComponent.h"

AAIEnemy::AAIEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AAIEnemy::BeginPlay()
{
	Super::BeginPlay();

	if (bPatrol)
	{
		MoveToNextPatrolPoint();
	}
}

void AAIEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (currentPatrolPoint)
	{
		FVector delta = GetActorLocation() - currentPatrolPoint->GetActorLocation();
		float distanceToGoal = delta.Size();

		if (distanceToGoal < 100)
		{
			MoveToNextPatrolPoint();
		}

	}
}

void AAIEnemy::MoveToNextPatrolPoint()
{
	for (int i = 0; i < patrolPoints.Num() + 1; i++)
	{
		if (currentPatrolPoint == nullptr || currentPatrolPoint == patrolPoints[patrolPoints.Num() - 1])
		{
			currentPatrolPoint = patrolPoints[0];
			break;
		}
		else if (currentPatrolPoint == patrolPoints[i])
		{
			currentPatrolPoint = patrolPoints[i + 1];
			break;
		}
	}

	UAIBlueprintHelperLibrary::SimpleMoveToActor(GetController(), currentPatrolPoint);
}