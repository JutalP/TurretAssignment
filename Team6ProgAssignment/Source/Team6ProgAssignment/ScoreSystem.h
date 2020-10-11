#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ScoreSystem.generated.h"

UCLASS()
class TEAM6PROGASSIGNMENT_API AScoreSystem : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Score", meta = (AllowPrivateAccess = "true"))
		int currentScore = 0;

public:
	AScoreSystem();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	void AddScore();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score")
		int scoreGoal = 50;

	UFUNCTION(BlueprintCallable)
		void CompleteScore();

	//Triggers when score goal is complete
	UFUNCTION(BlueprintImplementableEvent)
		void BP_OnCompleteScore();
};
