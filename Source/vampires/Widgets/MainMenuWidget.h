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

	// TODO: Add options menu

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> NewGameButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> NewGameTextBlock;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> QuitButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> QuitTextBlock;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> NewGameMenuWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSoftObjectPtr<UWorld> NewGameLevel;

private:
	UPROPERTY()
	TObjectPtr<UUserWidget> CurrentNewGameWidget;

public:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void NewGameButtonOnClicked();

	UFUNCTION()
	void QuitButtonOnClicked();

	UFUNCTION()
	void NewGameTextBlockHoveredDelegate() { SetTextBlockHovered(NewGameTextBlock); }

	UFUNCTION()
	void NewGameTextBlockUnhoveredDelegate() { SetTextBlockUnhovered(NewGameTextBlock); }

	UFUNCTION()
	void QuitTextBlockHoveredDelegate() { SetTextBlockHovered(QuitTextBlock); }

	UFUNCTION()
	void QuitTextBlockUnhoveredDelegate() { SetTextBlockUnhovered(QuitTextBlock); }
};
