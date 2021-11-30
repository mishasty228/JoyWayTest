// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class JoyWayTest : ModuleRules
{
	public JoyWayTest(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
