// Louis Hobbs | 2024-2025

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VampireInteractiveWidget.generated.h"

/**
 * 
 */
UCLASS()
class VAMPIRES_API UVampireInteractiveWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	TObjectPtr<UUserWidget> CurrentFocus;

	bool GamepadConnected = false;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

public:
	UFUNCTION()
	void SetCurrentFocus(UUserWidget* UserWidget);
};
