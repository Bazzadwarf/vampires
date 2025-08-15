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

protected:
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UButton> ResumeButton;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UTextBlock> ResumeTextBlock;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UListView* UpgradesListView;

	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void ResumeButtonClicked();

	UFUNCTION()
	void ResumeButtonOnHovered();

	UFUNCTION()
	void ResumeButtonOnUnhovered();
};
