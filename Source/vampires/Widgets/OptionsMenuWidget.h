// Louis Hobbs | 2024-2025

#pragma once

#include "CoreMinimal.h"
#include "VampireInteractiveWidget.h"
#include "OptionsMenuWidget.generated.h"

class UCustomSlider;
class UCustomComboBoxString;
class USlider;
class UComboBoxString;
class UButton;
class UCustomButton;

/**
 * 
 */
UCLASS()
class VAMPIRES_API UOptionsMenuWidget : public UVampireInteractiveWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCustomComboBoxString> ResolutionComboBox;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCustomComboBoxString> WindowTypeComboBox;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCustomComboBoxString> VsyncComboBox;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCustomComboBoxString> RefreshRateComboBox;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCustomComboBoxString> DynamicResolutionComboBox;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCustomSlider> MasterAudioSlider;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> MasterAudioTextBlock;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCustomButton> ReturnButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCustomButton> ResetToDefaultsButton;

	UPROPERTY(EditDefaultsOnly, Category = "Widget Settings | New Game")
	TSubclassOf<UUserWidget> MainMenuMenuWidget;

	UPROPERTY(EditDefaultsOnly, Category = "Widget Settings | Sound Settings")
	TObjectPtr<USoundClass> MasterSoundClass = nullptr;
	
	UFUNCTION()
	virtual void NativeConstruct() override;

	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	void GenerateWindowTypeOptions();

	void GenerateResolutionOptions();

	void GenerateDynamicResolutionOptions();

	void GenerateVsyncOptions();

	void GenerateRefreshRateOptions();

	void GenerateAudioLevelOptions();

	UFUNCTION()
	void OnResolutionFocused(FFocusEvent InFocusEvent);

	UFUNCTION()
	void OnResolutionSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);

	UFUNCTION()
	void OnWindowTypeFocused(FFocusEvent InFocusEvent);

	UFUNCTION()
	void OnWindowTypeSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);
	void SetWindowModeFullscreen();
	void SetWindowModeWindowedFullscreen();
	void SetWindowModeWindowed();

	UFUNCTION()
	void OnDynamicResolutionFocused(FFocusEvent InFocusEvent);

	UFUNCTION()
	void OnDynamicResolutionSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);

	UFUNCTION()
	void OnVsyncFocused(FFocusEvent InFocusEvent);

	UFUNCTION()
	void OnVsyncSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);

	UFUNCTION()
	void OnRefreshRateFocused(FFocusEvent InFocusEvent);
	
	UFUNCTION()
	void OnRefreshRateSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);

	UFUNCTION()
	void OnAudioFocused(FFocusEvent InFocusEvent);
	
	UFUNCTION()
	void OnAudioLeverValueChanged(float Value);

	UFUNCTION()
	void OnResetToDefaultsFocused(FFocusEvent InFocusEvent);
	
	UFUNCTION()
	void ResetToDefaultsOnClicked();

	UFUNCTION()
	void OnReturnButtonFocused(FFocusEvent InFocusEvent);
	
	UFUNCTION()
	void ReturnButtonOnClicked();

	void GetListOfUniqueRefreshRates(TArray<uint32>& RefreshRates);
};
