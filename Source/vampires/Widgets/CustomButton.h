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

	UPROPERTY(BlueprintAssignable)
	FOnButtonHoverEventCustom OnUnhovered;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Button Settings | Text")
	FText ButtonText = FText::FromString("Default");

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Button Settings | Text")
	int TextSize = 30.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button Settings | Color")
	FLinearColor ButtonHoveredTextColor = {0, 1, 0, 1};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button Settings | Color")
	FLinearColor ButtonUnhoveredTextColor = {1, 1, 1, 1};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button Settings | Sound")
	TObjectPtr<USoundBase> ButtonClickedSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button Settings | Sound")
	TObjectPtr<USoundBase> ButtonPressedSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button Settings | Sound")
	TObjectPtr<USoundBase> ButtonReleasedSound;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button Settings | Sound")
	TObjectPtr<USoundBase> ButtonHoveredSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button Settings | Sound")
	TObjectPtr<USoundBase> ButtonUnhoveredSound;

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

	UFUNCTION()
	void OnButtonUnhovered();
};
