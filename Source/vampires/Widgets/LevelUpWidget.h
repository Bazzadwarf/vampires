// Louis Hobbs | 2024-2025

#pragma once

#include "CoreMinimal.h"
#include "VampireInteractiveWidget.h"
#include "LevelUpWidget.generated.h"

class UCustomButton;
class UUpgradeButtonWidget;
class UScrollBox;
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

public:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCustomButton> ResumeButton;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UScrollBox> UpgradesScrollBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UUpgradeButtonWidget> UpgradeButtonWidgetTemplate;

protected:
	virtual void NativeConstruct() override;

	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

private:
	UFUNCTION()
	void ResumeButtonClicked();

	UFUNCTION()
	void BackButtonFocused(FFocusEvent InFocusEvent);
};
