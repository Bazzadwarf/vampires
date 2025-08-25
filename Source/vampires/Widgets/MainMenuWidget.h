// Louis Hobbs | 2024-2025

#pragma once

#include "CoreMinimal.h"
#include "VampireInteractiveWidget.h"
#include "MainMenuWidget.generated.h"

class UCustomButton;
class UButton;
/**
 * 
 */
UCLASS()
class VAMPIRES_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCustomButton> NewGameButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCustomButton> OptionsButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCustomButton> QuitButton;

	UPROPERTY(EditDefaultsOnly, Category = "Widget Settings | New Game")
	TSubclassOf<UUserWidget> NewGameMenuWidget;

	UPROPERTY(EditDefaultsOnly, Category = "Widget Settings | New Game")
	TSoftObjectPtr<UWorld> NewGameLevel;

	UPROPERTY(EditDefaultsOnly, Category = "Widget Settings | Options")
	TSubclassOf<UUserWidget> OptionsMenuWidget;

public:
	virtual void NativeConstruct() override;

protected:
	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

private:
	UFUNCTION()
	void NewGameButtonOnClicked();

	UFUNCTION()
	void OptionsButtonOnClicked();

	UFUNCTION()
	void QuitButtonOnClicked();
};
