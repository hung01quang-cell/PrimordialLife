// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class PrimordialLife : ModuleRules
{
	public PrimordialLife(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate",
            "GameplayTags",
            "GameplayTasks",
            "AnimGraphRuntime",
            "MotionWarping",
            "Niagara",
            "NavigationSystem"
        });

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"PrimordialLife",
			"PrimordialLife/Variant_Platforming",
			"PrimordialLife/Variant_Platforming/Animation",
			"PrimordialLife/Variant_Combat",
			"PrimordialLife/Variant_Combat/AI",
			"PrimordialLife/Variant_Combat/Animation",
			"PrimordialLife/Variant_Combat/Gameplay",
			"PrimordialLife/Variant_Combat/Interfaces",
			"PrimordialLife/Variant_Combat/UI",
			"PrimordialLife/Variant_SideScrolling",
			"PrimordialLife/Variant_SideScrolling/AI",
			"PrimordialLife/Variant_SideScrolling/Gameplay",
			"PrimordialLife/Variant_SideScrolling/Interfaces",
			"PrimordialLife/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
