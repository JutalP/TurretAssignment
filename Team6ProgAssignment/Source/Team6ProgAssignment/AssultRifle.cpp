#include "AssultRifle.h"
#include "ScoreSystem.h"
#include "DrawDebugHelpers.h"

AAssultRifle::AAssultRifle()
{
	PrimaryActorTick.bCanEverTick = true;

	scoreSystemRef = CreateDefaultSubobject<AScoreSystem>(TEXT("ScoreSystemRef"));

	gunName = "Assult Rifle";
	ammo = 25;
	currentAmmo = ammo;
}

void AAssultRifle::BeginPlay()
{
	Super::BeginPlay();
}

void AAssultRifle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AAssultRifle::Fire(APawn* attackInstigator, const FVector& startLocation, const FVector& forwardVector)
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
			scoreSystemRef->AddScore();
			UE_LOG(LogTemp, Error, TEXT("Assult Rifle Fired"));
		}
	}

	currentAmmo -= 1;

	BP_OnFiredBullet(impactLocation, hit.Actor.Get());
}

bool AAssultRifle::Reload()
{
	if (currentAmmo != ammo)
	{
		currentAmmo = ammo;
		return true;
	}

	return false;
}

bool AAssultRifle::CheckCurrentAmmo()
{
	if (currentAmmo > 0)
	{
		return true;
	}

	return false;
}