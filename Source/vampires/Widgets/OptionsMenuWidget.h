// Louis Hobbs | 2024-2025

#pragma once

#include "CoreMinimal.h"
#include "VampireInteractiveWidget.h"
#include "OptionsMenuWidget.generated.h"

class UComboBoxString;
class UComboBox;
class UComboBox;
class UButton;
/**
 * 
 */
UCLASS()
class VAMPIRES_API UOptionsMenuWidget : public UVampireInteractiveWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UComboBoxString> ResolutionComboBox;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ResolutionTextBlock;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UComboBoxString> WindowTypeComboBox;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UComboBoxString> VsyncComboBox;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UComboBoxString> RefreshRateComboBox;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UComboBoxString> DynamicResolutionComboBox;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ReturnButton;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ReturnBlock;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ResetToDefaultsButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ResetToDefaultsBlock;

	UPROPERTY(EditDefaultsOnly, Category = "Widget Settings | New Game")
	TSubclassOf<UUserWidget> MainMenuMenuWidget;

protected:
	virtual void NativeConstruct() override;

private:
	void GenerateResolutionOptions();
	
	UFUNCTION()
	void ReturnButtonOnClicked();

	UFUNCTION()
	void ReturnTextBlockHoveredDelegate() { SetTextBlockHovered(ReturnBlock); }

	UFUNCTION()
	void ReturnTextBlockUnhoveredDelegate() { SetTextBlockUnhovered(ReturnBlock); }
};
