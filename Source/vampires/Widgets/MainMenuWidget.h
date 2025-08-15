// Louis Hobbs | 2024-2025

#pragma once

#include "CoreMinimal.h"
#include "VampireInteractiveWidget.h"
#include "MainMenuWidget.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class VAMPIRES_API UMainMenuWidget : public UVampireInteractiveWidget
{
	GENERATED_BODY()
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> NewGameButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> NewGameTextBlock;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> OptionsButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> OptionsTextBlock;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> QuitButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> QuitTextBlock;

	UPROPERTY(EditDefaultsOnly, Category = "Widget Settings | New Game")
	TSubclassOf<UUserWidget> NewGameMenuWidget;

	UPROPERTY(EditDefaultsOnly, Category = "Widget Settings | New Game")
	TSoftObjectPtr<UWorld> NewGameLevel;

	UPROPERTY(EditDefaultsOnly, Category = "Widget Settings | Options")
	TSubclassOf<UUserWidget> OptionsMenuWidget;

public:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void NewGameButtonOnClicked();

	UFUNCTION()
	void OptionsButtonOnClicked();

	UFUNCTION()
	void QuitButtonOnClicked();

	UFUNCTION()
	void NewGameButtonOnHovered();

	UFUNCTION()
	void NewGameButtonOnUnhovered();

	UFUNCTION()
	void OptionsButtonOnHovered();

	UFUNCTION()
	void OptionsButtonOnUnhovered();

	UFUNCTION()
	void QuitButtonOnHovered();

	UFUNCTION()
	void QuitButtonOnUnhovered();
};
