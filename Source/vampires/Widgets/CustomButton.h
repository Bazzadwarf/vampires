// Louis Hobbs | 2024-2025

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CustomButton.generated.h"

class UTextBlock;
class UButton;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonClickedEventCustom);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonPressedEventCustom);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonReleasedEventCustom);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonHoverEventCustom);

/**
 * 
 */
UCLASS()
class VAMPIRES_API UCustomButton : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FOnButtonClickedEventCustom OnClicked;

	UPROPERTY(BlueprintAssignable)
	FOnButtonPressedEventCustom OnPressed;

	UPROPERTY(BlueprintAssignable)
	FOnButtonReleasedEventCustom OnReleased;

	UPROPERTY(BlueprintAssignable)
	FOnButtonHoverEventCustom OnHovered;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText ButtonText = FText::FromString("Default");

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ButtonBody;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextBlock;

protected:
	
	virtual void NativeConstruct() override;

	virtual void SynchronizeProperties() override;

public:

	TObjectPtr<UTextBlock> GetTextBlock();

private:
	UFUNCTION()
	void OnButtonClicked();

	UFUNCTION()
	void OnButtonPressed();

	UFUNCTION()
	void OnButtonReleased();

	UFUNCTION()
	void OnButtonHovered();
};
