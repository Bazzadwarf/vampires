// Louis Hobbs | 2024-2025


#include "CustomSlider.h"

#include "Components/Slider.h"

void UCustomSlider::NativeConstruct()
{
	Super::NativeConstruct();

	SetIsFocusable(true);

	SliderBody->OnValueChanged.AddDynamic(this, &UCustomSlider::OnSliderValueChanged);

	SetDesiredFocusWidget(SliderBody);
}

void UCustomSlider::NativeOnAddedToFocusPath(const FFocusEvent& InFocusEvent)
{
	Super::NativeOnAddedToFocusPath(InFocusEvent);
	OnFocused.Broadcast(InFocusEvent);
}

void UCustomSlider::NativeOnRemovedFromFocusPath(const FFocusEvent& InFocusEvent)
{
	Super::NativeOnRemovedFromFocusPath(InFocusEvent);
	OnUnfocused.Broadcast(InFocusEvent);
}

void UCustomSlider::OnSliderValueChanged(float Value)
{
	OnValueChanged.Broadcast(Value);
}
