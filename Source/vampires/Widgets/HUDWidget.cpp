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

void UHUDWidget::UpdateTimerBlock()
{
}

void UHUDWidget::UpdateKillBlock(int killCount)
{
	KillBLock->SetText(FText::FromString("Kills: " + FString::FromInt(killCount)));
}
