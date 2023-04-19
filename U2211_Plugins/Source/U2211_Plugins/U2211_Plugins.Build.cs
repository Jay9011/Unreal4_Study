// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class U2211_Plugins : ModuleRules
{
	public U2211_Plugins(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        
        PublicIncludePaths.Add(ModuleDirectory);
        
        PublicDependencyModuleNames.Add("Core");
        PublicDependencyModuleNames.Add("CoreUObject");
        PublicDependencyModuleNames.Add("Engine");
        PublicDependencyModuleNames.Add("InputCore");
        PublicDependencyModuleNames.Add("HeadMountedDisplay");
        PublicDependencyModuleNames.Add("NavigationSystem");
        PublicDependencyModuleNames.Add("AIModule");
        PublicDependencyModuleNames.Add("ProceduralMeshComponent");
    }
}
