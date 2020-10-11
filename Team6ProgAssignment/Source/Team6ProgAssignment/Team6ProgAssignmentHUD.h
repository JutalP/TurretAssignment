// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Team6ProgAssignmentHUD.generated.h"

UCLASS()
class ATeam6ProgAssignmentHUD : public AHUD
{
	GENERATED_BODY()

public:
	ATeam6ProgAssignmentHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;
};

