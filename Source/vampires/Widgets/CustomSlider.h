// Louis Hobbs | 2024-2025

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CustomSlider.generated.h"

class USlider;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFloatValueChangedEventCustom, float, Value);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCustomSliderFocusPath, FFocusEvent, InFocusEvent);


/**
 * 
 */
UCLASS()
class VAMPIRES_API UCustomSlider : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FOnFloatValueChangedEventCustom OnValueChanged;

	UPROPERTY(BlueprintAssignable)
	FCustomSliderFocusPath OnFocused;

	UPROPERTY(BlueprintAssignable)
	FCustomSliderFocusPath OnUnfocused;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USlider> SliderBody;

protected:
	virtual void NativeConstruct() override;

	virtual void NativeOnAddedToFocusPath(const FFocusEvent& InFocusEvent) override;

	virtual void NativeOnRemovedFromFocusPath(const FFocusEvent& InFocusEvent) override;

	UFUNCTION()
	void OnSliderValueChanged(float Value);
	
};
