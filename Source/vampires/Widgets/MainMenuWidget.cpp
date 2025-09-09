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
		NewGameButton->OnFocused.AddUniqueDynamic(this, &UMainMenuWidget::NewGameButtonFocused);
	}

	if (OptionsButton)
	{
		OptionsButton->OnClicked.AddUniqueDynamic(this, &UMainMenuWidget::OptionsButtonOnClicked);
		OptionsButton->OnFocused.AddUniqueDynamic(this, &UMainMenuWidget::OptionsButtonFocused);
	}

	if (QuitButton)
	{
		QuitButton->OnClicked.AddUniqueDynamic(this, &UMainMenuWidget::QuitButtonOnClicked);
		QuitButton->OnFocused.AddUniqueDynamic(this, &UMainMenuWidget::QuitButtonFocused);
	}

	QuitButton->SetIsEnabled(false);

	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(PlayerController, NewGameButton, EMouseLockMode::LockAlways);
		PlayerController->bShowMouseCursor = true;
	}

	NewGameButton->SetKeyboardFocus();
}

FReply UMainMenuWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	CurrentFocus->SetKeyboardFocus();

	return Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);
}

UCustomButton* UMainMenuWidget::GetNewGameButton()
{
	return NewGameButton;
}

UCustomButton* UMainMenuWidget::GetOptionsButton()
{
	return OptionsButton;
}

UCustomButton* UMainMenuWidget::GetQuitButton()
{
	return QuitButton;
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

void UMainMenuWidget::NewGameButtonFocused(FFocusEvent InFocusEvent)
{
	SetCurrentFocus(NewGameButton);
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

void UMainMenuWidget::OptionsButtonFocused(FFocusEvent InFocusEvent)
{
	SetCurrentFocus(OptionsButton);
}

void UMainMenuWidget::QuitButtonOnClicked()
{
	// TODO: Add platform specific Exit requests
	// This is not a bit deal for the moment as we are only building for windows
	// For some reason the generic version does not work the same as FWindowsPlatformMisc
	FWindowsPlatformMisc::RequestExit(false);
}

void UMainMenuWidget::QuitButtonFocused(FFocusEvent InFocusEvent)
{
	SetCurrentFocus(QuitButton);
}
