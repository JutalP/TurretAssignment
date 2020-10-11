#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseGun.generated.h"

//Forward Declaration
class USkeletalMeshComponent;

UCLASS()
class TEAM6PROGASSIGNMENT_API ABaseGun : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
		USkeletalMeshComponent* gunMesh;

public:
	ABaseGun();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ammo", meta = (AllowPrivateAccess = "true"))
		int currentAmmo = 0;
public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Name")
		FString gunName;

	UPROPERTY(EditAnywhere, Category = "GunSpecs")
		float bulletTravelLength = 10000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GunSpecs")
		int ammo;

	virtual	void Fire(APawn* attackInstigator, const FVector& startLocation, const FVector& forwardVector);

	virtual bool CheckCurrentAmmo();

	virtual bool Reload();

	//Blueprint Event running at the end of the Fire function 
	UFUNCTION(BlueprintImplementableEvent)
		void BP_OnFiredBullet(const FVector& hitLocation, AActor* hitActor);
};