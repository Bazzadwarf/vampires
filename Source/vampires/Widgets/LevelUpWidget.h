// Louis Hobbs | 2024-2025

#pragma once

#include "CoreMinimal.h"
#include "VampireInteractiveWidget.h"
#include "LevelUpWidget.generated.h"

class UUpgradeButtonDataObject;
class UListView;
class UButton;
/**
 * 
 */
UCLASS(Blueprintable)
class VAMPIRES_API ULevelUpWidget : public UVampireInteractiveWidget
{
	GENERATED_BODY()

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> ResumeButton;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> ResumeTextBlock;

	UPROPERTY(meta=(BindWidget))
	UListView* UpgradesListView;

	virtual void NativeConstruct() override;

	UFUNCTION()
	void ResumeButtonClicked();

	UFUNCTION()
	void ResumeButtonOnHovered();

	UFUNCTION()
	void ResumeButtonOnUnhovered();
};
