// Louis Hobbs | 2024-2025


#include "HUDWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UHUDWidget::UpdateEXPBar(float CurrentLevelPercent)
{
	EXPbar->SetPercent(CurrentLevelPercent);
}

void UHUDWidget::UpdateLevelBlock(int Level)
{
	LevelBlock->SetText(FText::FromString("LV" + FString::FromInt(Level)));
}

void UHUDWidget::UpdateTimerBlock(float DeltaTime)
{
	int TimeSinceStart = FMath::FloorToInt(DeltaTime);

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

	TimerBLock->SetText(FText::FromString(Mins + ":" + Secs));
}

void UHUDWidget::UpdateKillBlock(int KillCount)
{
	KillBLock->SetText(FText::FromString("Kills: " + FString::FromInt(KillCount)));
}

void UHUDWidget::UpdateGoldBlock(int GoldCount)
{
	GoldBLock->SetText(FText::FromString("Gold: " + FString::FromInt(GoldCount)));
}
