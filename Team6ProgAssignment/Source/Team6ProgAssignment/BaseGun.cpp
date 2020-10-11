#include "BaseGun.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"

ABaseGun::ABaseGun()
{
	PrimaryActorTick.bCanEverTick = true;

	gunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	gunMesh->SetupAttachment(RootComponent);
}

void ABaseGun::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseGun::Fire(APawn* attackInstigator, const FVector& startLocation, const FVector& forwardVector)
{
	TArray<AActor*> ignoreActors;
	ignoreActors.Add(this);
	ignoreActors.Add(attackInstigator);

	FHitResult hit;
	const FVector endLocation = startLocation + (forwardVector * bulletTravelLength);

	FCollisionQueryParams params;
	params.AddIgnoredActors(ignoreActors);

	GetWorld()->LineTraceSingleByChannel(hit, startLocation, endLocation, ECC_Visibility, params);
	DrawDebugLine(GetWorld(), startLocation, endLocation, FColor::White);

	const FVector impactLocation = hit.bBlockingHit ? hit.ImpactPoint : endLocation;

	if (hit.bBlockingHit && hit.Actor.IsValid())
	{

		if (hit.GetActor()->GetName() == "BP_Enemy_2")
		{
			UE_LOG(LogTemp, Error, TEXT("Hej Anton :)"));
		}
	}

	currentAmmo -= 1;

	BP_OnFiredBullet(impactLocation, hit.Actor.Get());
}

bool ABaseGun::CheckCurrentAmmo()
{
	if (currentAmmo > 0)
	{
		return true;
	}

	return false;
}

bool ABaseGun::Reload()
{
	if (currentAmmo != ammo)
	{
		currentAmmo = ammo;
		return true;
	}

	return false;
}