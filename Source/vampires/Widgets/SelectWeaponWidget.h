// Louis Hobbs | 2024-2025

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class VAMPIRES_API SelectWeaponWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SelectWeaponWidget)
		{
		}

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
};
