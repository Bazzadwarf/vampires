// Louis Hobbs | 2024-2025

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LevelUpWidget.generated.h"

class UUpgradeButtonDataObject;
class UListView;
class UButton;
/**
 * 
 */
UCLASS(Blueprintable)
class VAMPIRES_API ULevelUpWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UButton* ResumeButton;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UListView* UpgradesListView;

	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void ResumeButtonClicked();
};
