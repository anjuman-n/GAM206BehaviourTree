// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class PlayerCharacter : ModuleRules
{
	public PlayerCharacter(ReadOnlyTargetRules Target) : base(Target)
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
			"SlateCore",
			"NavigationSystem"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"PlayerCharacter",
			"PlayerCharacter/Variant_Platforming",
			"PlayerCharacter/Variant_Platforming/Animation",
			"PlayerCharacter/Variant_Combat",
			"PlayerCharacter/Variant_Combat/AI",
			"PlayerCharacter/Variant_Combat/Animation",
			"PlayerCharacter/Variant_Combat/Gameplay",
			"PlayerCharacter/Variant_Combat/Interfaces",
			"PlayerCharacter/Variant_Combat/UI",
			"PlayerCharacter/Variant_SideScrolling",
			"PlayerCharacter/Variant_SideScrolling/AI",
			"PlayerCharacter/Variant_SideScrolling/Gameplay",
			"PlayerCharacter/Variant_SideScrolling/Interfaces",
			"PlayerCharacter/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
