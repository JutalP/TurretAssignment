#include "AssultRifleTurret.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "AssultRifle.h"
#include "Math/UnrealMathUtility.h"

AAssultRifleTurret::AAssultRifleTurret()
{
	PrimaryActorTick.bCanEverTick = true;

	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	springArm->SetupAttachment(RootComponent);

	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	camera->SetupAttachment(springArm);
}

void AAssultRifleTurret::BeginPlay()
{
	Super::BeginPlay();

	AAssultRifle* newAssultRifleInstance = GetWorld()->SpawnActor<AAssultRifle>(startingWeapon);
	if (newAssultRifleInstance != nullptr)
	{
		assultRifle = newAssultRifleInstance;
		assultRifle->AttachToComponent(turretMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, "GripPoint");
	}
}

void AAssultRifleTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bFiring)
	{
		TryFire();
	}

	{
		FRotator newRotation = GetActorRotation();
		newRotation.Yaw += cameraInput.X;
		SetActorRotation(newRotation);
	}

	{
		FRotator newRotation = springArm->GetComponentRotation();
		newRotation.Pitch = FMath::Clamp(newRotation.Pitch + cameraInput.Y, -80.0f, 80.f);
		springArm->SetWorldRotation(newRotation);
	}
}

void AAssultRifleTurret::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Turn", this, &AAssultRifleTurret::CameraYaw);
	PlayerInputComponent->BindAxis("LookUp", this, &AAssultRifleTurret::CameraPitch);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AAssultRifleTurret::FirePressed);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AAssultRifleTurret::FireReleased);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &AAssultRifleTurret::Reload);
}

void AAssultRifleTurret::CameraPitch(float value)
{
	cameraInput.Y = value;
}

void AAssultRifleTurret::CameraYaw(float value)
{
	cameraInput.X = value;
}

bool AAssultRifleTurret::TryFire()
{
	if (assultRifle != nullptr)
	{
		if (assultRifle->CheckCurrentAmmo())
		{
			FVector spawnLocation = camera->GetComponentLocation();
			FRotator spawnRotation = camera->GetComponentRotation();
			assultRifle->Fire(this, spawnLocation, spawnRotation.Vector());
			BP_OnFireWithWeapon();
		}
	}

	return false;
}

void AAssultRifleTurret::FirePressed()
{
	bFiring = true;
}

void AAssultRifleTurret::FireReleased()
{
	bFiring = false;
}

void AAssultRifleTurret::Reload()
{
	if (assultRifle != nullptr)
	{
		if (assultRifle->Reload())
		{
			BP_OnReloadWeapon();
		}
	}
}

FVector AAssultRifleTurret::GetPawnViewLocation() const
{
	if (camera)
	{
		return camera->GetComponentLocation();
	}

	return Super::GetPawnViewLocation();
}