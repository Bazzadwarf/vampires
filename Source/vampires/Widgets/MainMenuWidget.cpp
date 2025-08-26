// Louis Hobbs | 2024-2025


#include "MainMenuWidget.h"

#include "CustomButton.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (NewGameButton)
	{
		NewGameButton->OnClicked.AddUniqueDynamic(this, &UMainMenuWidget::NewGameButtonOnClicked);
	}

	if (OptionsButton)
	{
		OptionsButton->OnClicked.AddUniqueDynamic(this, &UMainMenuWidget::OptionsButtonOnClicked);
	}

	if (QuitButton)
	{
		QuitButton->OnClicked.AddUniqueDynamic(this, &UMainMenuWidget::QuitButtonOnClicked);
	}

	QuitButton->SetIsEnabled(false);

	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(PlayerController, NewGameButton, EMouseLockMode::LockAlways);
		PlayerController->bShowMouseCursor = true;
	}
}

FReply UMainMenuWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	NewGameButton->SetKeyboardFocus();

	return Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);
}

void UMainMenuWidget::NewGameButtonOnClicked()
{
	if (NewGameMenuWidget)
	{
		RemoveFromParent();

		UUserWidget* SelectWeaponWidget = CreateWidget<UUserWidget, APlayerController*>(
			UGameplayStatics::GetPlayerController(GetWorld(), 0), NewGameMenuWidget);

		if (SelectWeaponWidget)
		{
			SelectWeaponWidget->AddToViewport();
		}
	}
}

void UMainMenuWidget::OptionsButtonOnClicked()
{
	if (OptionsMenuWidget)
	{
		RemoveFromParent();

		UUserWidget* OptionWeaponWidget = CreateWidget<UUserWidget, APlayerController*>(
			UGameplayStatics::GetPlayerController(GetWorld(), 0), OptionsMenuWidget);

		if (OptionWeaponWidget)
		{
			OptionWeaponWidget->AddToViewport();
		}
	}
}

void UMainMenuWidget::QuitButtonOnClicked()
{
	// TODO: Add platform specific Exit requests
	// This is not a bit deal for the moment as we are only building for windows
	// For some reason the generic version does not work the same as FWindowsPlatformMisc
	FWindowsPlatformMisc::RequestExit(false);
}
