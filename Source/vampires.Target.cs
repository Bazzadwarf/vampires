// Louis Hobbs | 2024-2025

using UnrealBuildTool;
using System.Collections.Generic;

public class vampiresTarget : TargetRules
{
	public vampiresTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_4;
		ExtraModuleNames.AddRange( new string[] { "vampires" } );
	}
}
