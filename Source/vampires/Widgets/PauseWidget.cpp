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

	SetIsFocusable(false);
	
	if (ResumeButton)
	{
		ResumeButton->OnClicked.AddUniqueDynamic(this, &UPauseWidget::ResumeButtonOnClicked);
		ResumeButton->OnFocused.AddUniqueDynamic(this, &UPauseWidget::ResumeButtonOnFocused);
	}

	if (ReturnToMainMenuButton)
	{
		ReturnToMainMenuButton->OnClicked.AddUniqueDynamic(this, &UPauseWidget::ReturnToMainMenuButtonOnClicked);
		ReturnToMainMenuButton->OnFocused.AddUniqueDynamic(this, &UPauseWidget::ReturnToMainMenuButtonOnFocused);
	}

	ResumeButton->SetKeyboardFocus();
}

FReply UPauseWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	CurrentFocus->SetKeyboardFocus();

	return Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);
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
}

void UPauseWidget::ResumeButtonOnFocused(FFocusEvent InFocusEvent)
{
	SetCurrentFocus(ResumeButton);
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

void UPauseWidget::ReturnToMainMenuButtonOnFocused(FFocusEvent InFocusEvent)
{
	SetCurrentFocus(ReturnToMainMenuButton);
}
