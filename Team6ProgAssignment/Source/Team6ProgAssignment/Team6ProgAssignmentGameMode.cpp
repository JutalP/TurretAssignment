// Copyright Epic Games, Inc. All Rights Reserved.

#include "Team6ProgAssignmentGameMode.h"
#include "Team6ProgAssignmentHUD.h"
#include "Team6ProgAssignmentCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATeam6ProgAssignmentGameMode::ATeam6ProgAssignmentGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/BluePrints/Pawns/BP_StartingTurret"));
	DefaultPawnClass = PlayerPawnClassFinder.Class; 

	// use our custom HUD class
	HUDClass = ATeam6ProgAssignmentHUD::StaticClass();
}
