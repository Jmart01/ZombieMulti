// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ZombieMulti : ModuleRules
{
	public ZombieMulti(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay","NetCore", "Networking"});
		PrivateDependencyModuleNames.AddRange(new string[]{"GameplayAbilities","GameplayTags","GameplayTasks"});
	}
}
