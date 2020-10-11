#pragma once

#include "CoreMinimal.h"
#include "BaseGun.h"
#include "Pistol.generated.h"

//Forward Declaration
class AScoreSystem;

UCLASS()
class TEAM6PROGASSIGNMENT_API APistol : public ABaseGun
{
	GENERATED_BODY()

public:
	APistol();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	AScoreSystem* scoreSystemRef;

	UFUNCTION(BlueprintCallable, Category = "GunFunction")
		virtual void Fire(APawn* attackInstigator, const FVector& startLocation, const FVector& forwardVector) override;

	UFUNCTION(BlueprintCallable, Category = "GunFunction")
		virtual bool Reload() override;

	UFUNCTION(BlueprintCallable, Category = "GunFunction")
		virtual bool CheckCurrentAmmo() override;
};