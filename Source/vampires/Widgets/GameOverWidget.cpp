// Louis Hobbs | 2024-2025


#include "GameOverWidget.h"

#include "CustomButton.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "vampires/VampireGameInstance.h"

void UGameOverWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetIsFocusable(false);
	
	if (ReturnButton)
	{
		ReturnButton->OnClicked.AddUniqueDynamic(this, &UGameOverWidget::ReturnButtonOnClicked);
		ReturnButton->OnFocused.AddUniqueDynamic(this, &UGameOverWidget::ReturnButtonOnFocused);
	}

	ReturnButton->SetKeyboardFocus();
}

FReply UGameOverWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	CurrentFocus->SetKeyboardFocus();
	
	return Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);
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

void UGameOverWidget::ReturnButtonOnClicked()
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

void UGameOverWidget::ReturnButtonOnFocused(FFocusEvent InFocusEvent)
{
	SetCurrentFocus(ReturnButton);
}
