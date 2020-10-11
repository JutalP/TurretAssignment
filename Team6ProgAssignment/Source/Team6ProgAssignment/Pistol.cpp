#include "Pistol.h"
#include "ScoreSystem.h"
#include "DrawDebugHelpers.h"

APistol::APistol()
{
	PrimaryActorTick.bCanEverTick = true;

	scoreSystemRef = CreateDefaultSubobject<AScoreSystem>(TEXT("ScoreSystemRef"));

	gunName = "Pistol";
	ammo = 10;
	currentAmmo = ammo;
}

void APistol::BeginPlay()
{
	Super::BeginPlay();
}

void APistol::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APistol::Fire(APawn* attackInstigator, const FVector& startLocation, const FVector& forwardVector)
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
			UE_LOG(LogTemp, Error, TEXT("Pistol Fired"));
		}
	}

	currentAmmo -= 1;

	BP_OnFiredBullet(impactLocation, hit.Actor.Get());
}

bool APistol::Reload()
{
	Super::Reload();

	if (currentAmmo != ammo)
	{
		currentAmmo = ammo;
		return true;
	}

	return false;
}

bool APistol::CheckCurrentAmmo()
{
	Super::CheckCurrentAmmo();

	if (currentAmmo > 0)
	{
		return true;
	}

	return false;
}