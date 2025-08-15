// Louis Hobbs | 2024-2025

#pragma once

#include "CoreMinimal.h"
#include "VampireInteractiveWidget.h"
#include "OptionsMenuWidget.generated.h"

class USlider;
class UComboBoxString;
class UButton;
/**
 * 
 */
UCLASS()
class VAMPIRES_API UOptionsMenuWidget : public UVampireInteractiveWidget
{
	GENERATED_BODY()

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
	TObjectPtr<USlider> MasterAudioSlider;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> MasterAudioTextBlock;

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

	UPROPERTY(EditDefaultsOnly, Category = "Widget Settings | Sound Settings")
	TObjectPtr<USoundClass> MasterSoundClass = nullptr;
	
	UFUNCTION()
	virtual void NativeConstruct() override;

	void GenerateWindowTypeOptions();

	void GenerateResolutionOptions();

	void GenerateDynamicResolutionOptions();

	void GenerateVsyncOptions();

	void GenerateRefreshRateOptions();

	void GenerateAudioLevelOptions();

	UFUNCTION()
	void OnResolutionSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);

	UFUNCTION()
	void OnWindowTypeSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);
	void SetWindowModeFullscreen();
	void SetWindowModeWindowedFullscreen();
	void SetWindowModeWindowed();

	UFUNCTION()
	void OnDynamicResolutionSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);

	UFUNCTION()
	void OnVsyncSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);

	UFUNCTION()
	void OnRefreshRateSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);

	UFUNCTION()
	void OnAudioLeverValueChanged(float Value);

	UFUNCTION()
	void ResetToDefaultsOnClicked();
	
	UFUNCTION()
	void ReturnButtonOnClicked();

	UFUNCTION()
	void ResetToDefaultsButtonOnHovered();

	UFUNCTION()
	void ResetToDefaultsButtonOnUnhovered();

	UFUNCTION()
	void ReturnButtonOnHovered();

	UFUNCTION()
	void ReturnButtonOnUnhovered();

	void GetListOfUniqueRefreshRates(TArray<uint32>& RefreshRates);
};
