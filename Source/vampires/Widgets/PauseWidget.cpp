// Louis Hobbs | 2024-2025


#include "PauseWidget.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UPauseWidget::Init()
{
}

void UPauseWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ResumeButton)
	{
		ResumeButton->OnClicked.AddUniqueDynamic(this, &UPauseWidget::ResumeButtonClicked);
	}

	SetIsFocusable(true);
}

void UPauseWidget::ResumeButtonClicked()
{
	RemoveFromParent();

	if (APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(playerController);
		playerController->bShowMouseCursor = false;
		playerController->SetPause(false);
	}

	SetIsFocusable(false);
}
