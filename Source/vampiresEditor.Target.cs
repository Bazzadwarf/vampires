// Louis Hobbs | 2024-2025

using UnrealBuildTool;
using System.Collections.Generic;

public class vampiresEditorTarget : TargetRules
{
	public vampiresEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		ExtraModuleNames.AddRange( new string[] { "vampires" } );
	}
}
