// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class U2211_Plugins : ModuleRules
{
	public U2211_Plugins(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "NavigationSystem", "AIModule" });
    }
}
