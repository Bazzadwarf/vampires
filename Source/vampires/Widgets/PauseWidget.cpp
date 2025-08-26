// Louis Hobbs | 2024-2025


#include "PauseWidget.h"

#include "CustomButton.h"
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
	}

	if (ReturnToMainMenuButton)
	{
		ReturnToMainMenuButton->OnClicked.AddUniqueDynamic(this, &UPauseWidget::ReturnToMainMenuButtonOnClicked);
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
