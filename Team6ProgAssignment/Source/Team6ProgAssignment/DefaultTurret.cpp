#include "DefaultTurret.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Pistol.h"
#include "Math/UnrealMathUtility.h"

ADefaultTurret::ADefaultTurret()
{
	PrimaryActorTick.bCanEverTick = true;

	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	springArm->SetupAttachment(RootComponent);

	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	camera->SetupAttachment(springArm);
}

void ADefaultTurret::BeginPlay()
{
	Super::BeginPlay();
	
	APistol* newPistolInstance = GetWorld()->SpawnActor<APistol>(startingWeapon);
	if (newPistolInstance != nullptr)
	{
		pistol = newPistolInstance;
		pistol->AttachToComponent(turretMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, "GripPoint");
	}
}

void ADefaultTurret::Tick(float DeltaTime)
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

void ADefaultTurret::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Turn", this, &ADefaultTurret::CameraYaw);
	PlayerInputComponent->BindAxis("LookUp", this, &ADefaultTurret::CameraPitch);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ADefaultTurret::FirePressed);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &ADefaultTurret::FireReleased);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &ADefaultTurret::Reload);
}

void ADefaultTurret::CameraPitch(float value)
{
	cameraInput.Y = value;
}

void ADefaultTurret::CameraYaw(float value)
{
	cameraInput.X = value;
}

bool ADefaultTurret::TryFire()
{
	if (pistol != nullptr)
	{
		if (pistol->CheckCurrentAmmo())
		{
			FVector spawnLocation = camera->GetComponentLocation();
			FRotator spawnRotation = camera->GetComponentRotation();
			pistol->Fire(this, spawnLocation, spawnRotation.Vector());
			BP_OnFireWithWeapon();
		}
	}

	return false;
}

void ADefaultTurret::FirePressed()
{
	bFiring = true;
}

void ADefaultTurret::FireReleased()
{
	bFiring = false;
}

void ADefaultTurret::Reload()
{
	if (pistol != nullptr)
	{
		if (pistol->Reload())
		{
			BP_OnReloadWeapon();
		}
	}
}

FVector ADefaultTurret::GetPawnViewLocation() const
{
	if (camera)
	{
		return camera->GetComponentLocation();
	}

	return Super::GetPawnViewLocation();
}