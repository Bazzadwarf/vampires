// Louis Hobbs | 2024-2025


#include "VampireInteractiveWidget.h"

#include "vampires/DetectGamepad.h"

void UVampireInteractiveWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	GamepadConnected = UDetectGamepad::IsControllerConnected();
}

FReply UVampireInteractiveWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	return Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);
}

void UVampireInteractiveWidget::SetCurrentFocus(UUserWidget* UserWidget)
{
	CurrentFocus = UserWidget;
}
