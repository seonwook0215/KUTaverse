// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class KUTaverse : ModuleRules
{
	public KUTaverse(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore","HTTP", "EnhancedInput", "WebSockets", "Json", "JsonUtilities","UMG","Niagara" });

		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		if(Target.Platform== UnrealTargetPlatform.Android)
		{
			var manifestFile = Path.Combine(ModuleDirectory, "AndroidSanitizePermissions_UPL.xml");
			AdditionalPropertiesForReceipt.Add("AndroidPlugin", manifestFile);
		}
	}
}
