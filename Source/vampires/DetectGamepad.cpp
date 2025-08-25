// Louis Hobbs | 2024-2025


#include "DetectGamepad.h"

bool UDetectGamepad::IsControllerConnected()
{
	TSharedPtr<class GenericApplication> Game = FSlateApplication::Get().GetPlatformApplication();

	if (Game.Get() != nullptr && Game->IsGamepadAttached())
	{
		return true;
	}

	return false;
}
