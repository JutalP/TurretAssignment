// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Team6ProgAssignment : ModuleRules
{
	public Team6ProgAssignment(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
