// Louis Hobbs | 2024-2025

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CustomComboBoxString.generated.h"

class UComboBoxString;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnComboBoxOpeningCustom);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnComboBoxSelectionChangedCustom,
                                             FString, SelectedItem,
                                             ESelectInfo::Type, SelectionType);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCustomComboBoxFocusPath, FFocusEvent, InFocusEvent);

/**
 * 
 */
UCLASS()
class VAMPIRES_API UCustomComboBoxString : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnComboBoxOpeningCustom OnOpening;

	UPROPERTY(BlueprintAssignable)
	FOnComboBoxSelectionChangedCustom OnSelectionChanged;

	UPROPERTY(BlueprintAssignable)
	FCustomComboBoxFocusPath OnFocused;

	UPROPERTY(BlueprintAssignable)
	FCustomComboBoxFocusPath OnUnfocused;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UComboBoxString> ComboBox;

protected:
	virtual void NativeConstruct() override;

	virtual void NativeOnAddedToFocusPath(const FFocusEvent& InFocusEvent) override;

	virtual void NativeOnRemovedFromFocusPath(const FFocusEvent& InFocusEvent) override;

	UFUNCTION()
	void OnComboBoxOpening();

	UFUNCTION()
	void OnComboBoxSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType);
};
