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
		NewGameButton->OnClicked.AddUniqueDynamic(this, &UMainMenuWidget::PlayClickedSound);

		NewGameButton->OnHovered.AddUniqueDynamic(this, &UMainMenuWidget::PlayHoveredSound);
		NewGameButton->OnHovered.AddUniqueDynamic(this, &UMainMenuWidget::NewGameTextBlockHoveredDelegate);

		NewGameButton->OnUnhovered.AddUniqueDynamic(this, &UMainMenuWidget::NewGameTextBlockUnhoveredDelegate);
		NewGameButton->OnUnhovered.AddUniqueDynamic(this, &UMainMenuWidget::PlayUnhoveredSound);
	}

	if (QuitButton)
	{
		QuitButton->OnClicked.AddUniqueDynamic(this, &UMainMenuWidget::QuitButtonOnClicked);
		QuitButton->OnClicked.AddUniqueDynamic(this, &UMainMenuWidget::PlayClickedSound);

		QuitButton->OnHovered.AddUniqueDynamic(this, &UMainMenuWidget::PlayHoveredSound);
		QuitButton->OnHovered.AddUniqueDynamic(this, &UMainMenuWidget::QuitTextBlockHoveredDelegate);

		QuitButton->OnUnhovered.AddUniqueDynamic(this, &UMainMenuWidget::QuitTextBlockUnhoveredDelegate);
		QuitButton->OnUnhovered.AddUniqueDynamic(this, &UMainMenuWidget::PlayUnhoveredSound);
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

void UMainMenuWidget::QuitButtonOnClicked()
{
	// TODO: Add platform specific Exit requests
	// This is not a bit deal for the moment as we are only building for windows
	// For some reason the generic version does not work the same as FWindowsPlatformMisc
	FWindowsPlatformMisc::RequestExit(false);
}
