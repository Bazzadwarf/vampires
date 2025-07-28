// Louis Hobbs | 2024-2025

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VampireInteractiveWidget.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class VAMPIRES_API UVampireInteractiveWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<USoundBase> ButtonHoveredSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FLinearColor ButtonHoveredTextColor = {0, 1, 0, 1};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FLinearColor ButtonUnhoveredTextColor = {1, 1, 1, 1};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<USoundBase> ButtonUnhoveredSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<USoundBase> ButtonClickedSound;

protected:
	UPROPERTY()
	TObjectPtr<UUserWidget> PreviousScreen;

public:
	UFUNCTION()
	void SetReturnScreen(UUserWidget* UserWidget);

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
