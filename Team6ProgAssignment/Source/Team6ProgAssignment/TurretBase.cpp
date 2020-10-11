#include "TurretBase.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"

ATurretBase::ATurretBase()
{
	PrimaryActorTick.bCanEverTick = true;

	collision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("RootComponent"));
	RootComponent = collision;

	baseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	baseMesh->SetupAttachment(collision);

	turretMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("TurretMesh"));
	turretMesh->SetupAttachment(collision);
}

void ATurretBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATurretBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATurretBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

