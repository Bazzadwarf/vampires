// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDWidget.h"

#include "Components/ProgressBar.h"

void UHUDWidget::Init()
{
}

void UHUDWidget::UpdateEXPBar(float currentLevelPercent)
{
	EXPbar->SetPercent(currentLevelPercent);
}

void UHUDWidget::UpdateLevelBlock()
{
}

void UHUDWidget::UpdateTimerBlock()
{
}
