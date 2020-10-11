#pragma once

#include "CoreMinimal.h"
#include "TurretBase.h"
#include "AssultRifleTurret.generated.h"

//Forward Declaration
class UCameraComponent;
class USpringArmComponent;
class AAssultRifle;

UCLASS()
class TEAM6PROGASSIGNMENT_API AAssultRifleTurret : public ATurretBase
{
	GENERATED_BODY()

public:
	AAssultRifleTurret();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
		UCameraComponent* camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
		USpringArmComponent* springArm;

	FVector2D cameraInput;

protected:
	virtual void BeginPlay() override;

	bool bFiring = false;

	UFUNCTION()
		void FirePressed();

	UFUNCTION()
		void FireReleased();

	UPROPERTY(Transient)
		AAssultRifle* assultRifle = nullptr;

	UFUNCTION()
		void CameraYaw(float value);

	UFUNCTION()
		void CameraPitch(float value);
public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = "Weapon")
		TSubclassOf<AAssultRifle> startingWeapon;

	UFUNCTION(BlueprintCallable)
		bool TryFire();

	UFUNCTION(BlueprintCallable)
		void Reload();

	virtual FVector GetPawnViewLocation() const override;

	//Blueprint Event running when attacking
	UFUNCTION(BlueprintImplementableEvent)
		void BP_OnFireWithWeapon();

	UFUNCTION(BlueprintImplementableEvent)
		void BP_OnReloadWeapon();
};
