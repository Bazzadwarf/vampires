// Louis Hobbs | 2024-2025


#include "MainMenuWidget.h"

#include "SelectWeaponWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (NewGameButton)
	{
		NewGameButton->OnClicked.AddUniqueDynamic(this, &UMainMenuWidget::NewGameButtonOnClicked);
		NewGameButton->OnHovered.AddUniqueDynamic(this, &UMainMenuWidget::NewGameButtonOnHovered);
		NewGameButton->OnUnhovered.AddUniqueDynamic(this, &UMainMenuWidget::NewGameButtonOnUnhovered);
	}

	if (OptionsButton)
	{
		OptionsButton->OnClicked.AddUniqueDynamic(this, &UMainMenuWidget::OptionsButtonOnClicked);
		OptionsButton->OnHovered.AddUniqueDynamic(this, &UMainMenuWidget::OptionsButtonOnHovered);
		OptionsButton->OnUnhovered.AddUniqueDynamic(this, &UMainMenuWidget::OptionsButtonOnUnhovered);
	}

	if (QuitButton)
	{
		QuitButton->OnClicked.AddUniqueDynamic(this, &UMainMenuWidget::QuitButtonOnClicked);
		QuitButton->OnHovered.AddUniqueDynamic(this, &UMainMenuWidget::QuitButtonOnHovered);
		QuitButton->OnUnhovered.AddUniqueDynamic(this, &UMainMenuWidget::QuitButtonOnUnhovered);
	}

	QuitButton->SetIsEnabled(false);

	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(PlayerController, this, EMouseLockMode::LockAlways);
		PlayerController->bShowMouseCursor = true;
	}
}

void UMainMenuWidget::NewGameButtonOnClicked()
{
	PlayClickedSound();

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
	PlayClickedSound();

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
	PlayClickedSound();

	// TODO: Add platform specific Exit requests
	// This is not a bit deal for the moment as we are only building for windows
	// For some reason the generic version does not work the same as FWindowsPlatformMisc
	FWindowsPlatformMisc::RequestExit(false);
}

void UMainMenuWidget::NewGameButtonOnHovered()
{
	PlayHoveredSound();
	SetTextBlockHovered(NewGameTextBlock);
}

void UMainMenuWidget::NewGameButtonOnUnhovered()
{
	PlayUnhoveredSound();
	SetTextBlockUnhovered(NewGameTextBlock);
}

void UMainMenuWidget::OptionsButtonOnHovered()
{
	PlayHoveredSound();
	SetTextBlockHovered(OptionsTextBlock);
}

void UMainMenuWidget::OptionsButtonOnUnhovered()
{
	PlayUnhoveredSound();
	SetTextBlockUnhovered(OptionsTextBlock);
}

void UMainMenuWidget::QuitButtonOnHovered()
{
	PlayHoveredSound();
	SetTextBlockHovered(QuitTextBlock);
}

void UMainMenuWidget::QuitButtonOnUnhovered()
{
	PlayUnhoveredSound();
	SetTextBlockUnhovered(QuitTextBlock);
}
