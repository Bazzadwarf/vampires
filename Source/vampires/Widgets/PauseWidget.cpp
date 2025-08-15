// Louis Hobbs | 2024-2025


#include "PauseWidget.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "vampires/VampireGameInstance.h"

void UPauseWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ResumeButton)
	{
		ResumeButton->OnClicked.AddUniqueDynamic(this, &UPauseWidget::ResumeButtonOnClicked);
		ResumeButton->OnHovered.AddUniqueDynamic(this, &UPauseWidget::ResumeButtonOnHovered);
		ResumeButton->OnUnhovered.AddUniqueDynamic(this, &UPauseWidget::ResumeButtonOnUnhovered);
	}

	if (ReturnToMainMenuButton)
	{
		ReturnToMainMenuButton->OnClicked.AddUniqueDynamic(this, &UPauseWidget::ReturnToMainMenuButtonOnClicked);
		ReturnToMainMenuButton->OnHovered.AddUniqueDynamic(this, &UPauseWidget::ReturnToMainMenuButtonOnHovered);
		ReturnToMainMenuButton->OnUnhovered.AddUniqueDynamic(this, &UPauseWidget::ReturnToMainMenuButtonOnUnhovered);
	}

	SetIsFocusable(true);
}

void UPauseWidget::ResumeButtonOnClicked()
{
	RemoveFromParent();

	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(PlayerController);
		PlayerController->bShowMouseCursor = false;
		PlayerController->SetPause(false);
	}

	SetIsFocusable(false);
}


void UPauseWidget::ResumeButtonOnHovered()
{
	SetTextBlockHovered(ResumeTextBlock);
	PlayHoveredSound();
}

void UPauseWidget::ResumeButtonOnUnhovered()
{
	SetTextBlockUnhovered(ResumeTextBlock);
	PlayUnhoveredSound();
}

void UPauseWidget::ReturnToMainMenuButtonOnClicked()
{
	if (UVampireGameInstance* GameInstance = Cast<UVampireGameInstance>(GetGameInstance()))
	{
		if (!GameInstance->MainMenuWorld.IsNull())
		{
			UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), GameInstance->MainMenuWorld);

			if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
			{
				PlayerController->bShowMouseCursor = true;
			}
			SetIsFocusable(true);
		}
	}
}

void UPauseWidget::ReturnToMainMenuButtonOnHovered()
{
	SetTextBlockHovered(ReturnToMainMenuTextBlock);
	PlayHoveredSound();
}

void UPauseWidget::ReturnToMainMenuButtonOnUnhovered()
{
	SetTextBlockUnhovered(ReturnToMainMenuTextBlock);
	PlayUnhoveredSound();
}

