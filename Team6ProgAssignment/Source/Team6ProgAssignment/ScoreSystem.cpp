#include "ScoreSystem.h"

// Sets default values
AScoreSystem::AScoreSystem()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AScoreSystem::BeginPlay()
{
	Super::BeginPlay();

}

void AScoreSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AScoreSystem::AddScore()
{
	if (currentScore != scoreGoal)
	{
		currentScore += 1;
	}
	else
	{
		CompleteScore();
	}
}

void AScoreSystem::CompleteScore()
{
	if (currentScore == scoreGoal)
	{
		BP_OnCompleteScore();
	}
}