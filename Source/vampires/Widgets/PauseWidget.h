// Louis Hobbs | 2024-2025

#pragma once

#include "CoreMinimal.h"
#include "VampireInteractiveWidget.h"
#include "Blueprint/UserWidget.h"
#include "PauseWidget.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class VAMPIRES_API UPauseWidget : public UVampireInteractiveWidget
{
	GENERATED_BODY()
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> ResumeButton;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> ResumeTextBlock;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> ReturnToMainMenuButton;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> ReturnToMainMenuTextBlock;

	virtual void NativeConstruct() override;
	
	UFUNCTION()
	void ResumeButtonOnClicked();
	
	UFUNCTION()
	void ResumeButtonOnHovered();

	UFUNCTION()
	void ResumeButtonOnUnhovered();

	UFUNCTION()
	void ReturnToMainMenuButtonOnClicked();
	
	UFUNCTION()
	void ReturnToMainMenuButtonOnHovered();

	UFUNCTION()
	void ReturnToMainMenuButtonOnUnhovered();
	
};
