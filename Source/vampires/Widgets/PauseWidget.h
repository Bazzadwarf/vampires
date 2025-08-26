// Louis Hobbs | 2024-2025

#pragma once

#include "CoreMinimal.h"
#include "VampireInteractiveWidget.h"
#include "Blueprint/UserWidget.h"
#include "PauseWidget.generated.h"

class UCustomButton;

/**
 * 
 */
UCLASS()
class VAMPIRES_API UPauseWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCustomButton> ResumeButton;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCustomButton> ReturnToMainMenuButton;

	virtual void NativeConstruct() override;

	UFUNCTION()
	void ResumeButtonOnClicked();

	UFUNCTION()
	void ReturnToMainMenuButtonOnClicked();
};
