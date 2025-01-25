// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelUpWidget.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void ULevelUpWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ResumeButton)
	{
		ResumeButton->OnClicked.AddUniqueDynamic(this, &ULevelUpWidget::ResumeButtonClicked);
	}

	SetIsFocusable(true);
}

void ULevelUpWidget::ResumeButtonClicked()
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
