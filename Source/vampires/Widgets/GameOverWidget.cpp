// Louis Hobbs | 2024-2025


#include "GameOverWidget.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "vampires/VampireGameInstance.h"

void UGameOverWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ReturnButton)
	{
		ReturnButton->OnClicked.AddUniqueDynamic(this, &UGameOverWidget::ReturnButtonClicked);
	}
}

void UGameOverWidget::SetGameInfo(int Level, float Timer, int Kill, int Gold)
{
	// Set Level
	LevelBlock->SetText(FText::FromString(FString::FromInt(Level)));

	// Set timer
	int TimeSinceStart = FMath::FloorToInt(Timer);

	FString Mins = FString::FromInt(TimeSinceStart / 60);
	if (TimeSinceStart / 60 < 10)
	{
		Mins = "0" + Mins;
	}

	FString Secs = FString::FromInt(TimeSinceStart % 60);
	if (TimeSinceStart % 60 < 10)
	{
		Secs = "0" + Secs;
	}

	TimerBlock->SetText(FText::FromString(Mins + ":" + Secs));

	// Set Kill count
	KillBlock->SetText(FText::FromString(FString::FromInt(Kill)));

	// Set Gold count
	GoldBlock->SetText(FText::FromString(FString::FromInt(Gold)));
}

void UGameOverWidget::ReturnButtonClicked()
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
