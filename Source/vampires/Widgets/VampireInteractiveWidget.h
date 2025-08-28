// Louis Hobbs | 2024-2025

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VampireInteractiveWidget.generated.h"

class UCustomButton;
class UButton;
class UTextBlock;
/**
 * 
 */
UCLASS()
class VAMPIRES_API UVampireInteractiveWidget : public UUserWidget
{
	GENERATED_BODY()

	// TODO: Remove a lot of this stuff that has now been replaced by UCustomButton

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widget Settings | Sound")
	TObjectPtr<USoundBase> ButtonHoveredSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widget Settings | Color")
	FLinearColor ButtonHoveredTextColor = {0, 1, 0, 1};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widget Settings | Color")
	FLinearColor ButtonUnhoveredTextColor = {1, 1, 1, 1};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widget Settings | Sound")
	TObjectPtr<USoundBase> ButtonUnhoveredSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widget Settings | Sound")
	TObjectPtr<USoundBase> ButtonClickedSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widget Settings")
	TArray<TObjectPtr<UButton>> InteractableButtons;

	TObjectPtr<UUserWidget> CurrentFocus;

	UPROPERTY()
	TObjectPtr<UUserWidget> PreviousScreen;

	bool GamepadConnected = false;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

public:
	UFUNCTION()
	void SetReturnScreen(UUserWidget* UserWidget);

	UFUNCTION()
	void SetCurrentFocus(UUserWidget* UserWidget);

protected:
	UFUNCTION()
	void PlayHoveredSound();

	UFUNCTION()
	void SetTextBlockHovered(UTextBlock* TextBlock);

	UFUNCTION()
	void SetTextBlockUnhovered(UTextBlock* TextBlock);

	UFUNCTION()
	void PlayUnhoveredSound();

	UFUNCTION()
	void PlayClickedSound();

	UFUNCTION()
	void ReturnToPreviousScreen();
};
