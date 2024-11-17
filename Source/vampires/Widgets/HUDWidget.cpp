// Fill out your copyright notice in the Description page of Project Settings.


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

void UHUDWidget::UpdateTimerBlock(APawn* pawn)
{
	int timeSinceCreation = FMath::FloorToInt(pawn->GetGameTimeSinceCreation());

	FString mins = FString::FromInt(timeSinceCreation / 60);
	if (timeSinceCreation / 60 < 10)
	{
		mins = "0" + mins;	
	}
	
	FString secs = FString::FromInt(timeSinceCreation % 60);
	if (timeSinceCreation % 60 < 10)
	{
		secs = "0" + secs;
	}

	TimerBLock->SetText(FText::FromString(mins + ":" + secs));
}

void UHUDWidget::UpdateKillBlock(int killCount)
{
	KillBLock->SetText(FText::FromString("Kills: " + FString::FromInt(killCount)));
}
