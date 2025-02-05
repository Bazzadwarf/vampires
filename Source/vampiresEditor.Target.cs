// Louis Hobbs | 2024-2025

using UnrealBuildTool;
using System.Collections.Generic;

public class vampiresEditorTarget : TargetRules
{
	public vampiresEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_4;
		ExtraModuleNames.AddRange( new string[] { "vampires" } );
	}
}
