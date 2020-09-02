// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class StoneDefence : ModuleRules
{
	public StoneDefence(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		bEnableExceptions = true;

		PublicDependencyModuleNames.AddRange(new string[] 
		{ 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"AIModule",
			"UMG",
			"ApexDestruction",
			"StoneToolClass", 
			"SimpleScreenLoading" ,
			"SimpleArchives",
			"SimpleGameSettings",
			"SimpleTutorial",
			"Slate", 
			"SlateCore",
			"SimpleDrawText",
			"RawMesh"

		});

		if(Target.bBuildEditor == true)
        {
			PrivateDependencyModuleNames.AddRange(new string[] {
			
				"Persona"
			
			});
		}


		PrivateDependencyModuleNames.AddRange(new string[] {  });

        //Uncomment if you are using Slate UI
        //PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
