// Louis Hobbs | 2024-2025


#include "HUDWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UHUDWidget::Init()
{
}

void UHUDWidget::UpdateEXPBar(float currentLevelPercent)
{
	EXPbar->SetPercent(currentLevelPercent);
}

void UHUDWidget::UpdateLevelBlock(int level)
{
	LevelBlock->SetText(FText::FromString("LV" + FString::FromInt(level)));
}

void UHUDWidget::UpdateTimerBlock(float deltaTime)
{
	int timeSinceStart = FMath::FloorToInt(deltaTime);

	FString mins = FString::FromInt(timeSinceStart / 60);
	if (timeSinceStart / 60 < 10)
	{
		mins = "0" + mins;	
	}
	
	FString secs = FString::FromInt(timeSinceStart % 60);
	if (timeSinceStart % 60 < 10)
	{
		secs = "0" + secs;
	}

	TimerBLock->SetText(FText::FromString(mins + ":" + secs));
}

void UHUDWidget::UpdateKillBlock(int killCount)
{
	KillBLock->SetText(FText::FromString("Kills: " + FString::FromInt(killCount)));
}

void UHUDWidget::UpdateGoldBlock(int goldCount)
{
	GoldBLock->SetText(FText::FromString("Gold: " + FString::FromInt(goldCount)));
}
