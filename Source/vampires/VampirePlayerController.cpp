// Fill out your copyright notice in the Description page of Project Settings.


#include "VampirePlayerController.h"

#include "EXPComponent.h"
#include "HealthComponent.h"
#include "VampireGameMode.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/HUDWidget.h"

void AVampirePlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	if (PlayerHUD)
	{
		currentPlayerHUD = CreateWidget<UHUDWidget, AVampirePlayerController*>(this, PlayerHUD.Get());

		if (UEXPComponent* expComponent = aPawn->GetComponentByClass<UEXPComponent>())
		{
			expComponent->OnEXPGained.AddUniqueDynamic(this, &AVampirePlayerController::UpdatePlayerEXPHUD);
			expComponent->OnEXPLevelUp.AddUniqueDynamic(this, &AVampirePlayerController::UpdatePlayerLevelHUD);
			UpdatePlayerEXPHUD(expComponent->GetCurrentEXP(), expComponent->GetCurrentLevelPercent());
			UpdatePlayerLevelHUD(expComponent->GetCurrentLevel());
		}
		
		AVampireGameMode* gamemode = Cast<AVampireGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		if (gamemode)
		{
			gamemode->OnEnemyDeathCountIncrementDelegate.AddDynamic(this, &AVampirePlayerController::UpdateKillCountHUD);
			UpdateKillCountHUD(gamemode->GetEnemyDeathCount());
		}
		
		if (currentPlayerHUD)
		{
			currentPlayerHUD->AddToViewport();
		}
	}
}

void AVampirePlayerController::UpdatePlayerEXPHUD(int exp, float currentLevelPercent)
{
	if (currentPlayerHUD)
	{
		currentPlayerHUD->UpdateEXPBar(currentLevelPercent);
	}
}

void AVampirePlayerController::UpdatePlayerLevelHUD(int level)
{
	if (currentPlayerHUD)
	{
		currentPlayerHUD->UpdateLevelBlock(level);
	}
}

void AVampirePlayerController::UpdateKillCountHUD(int killCount)
{
	if (currentPlayerHUD)
	{
		currentPlayerHUD->UpdateKillBlock(killCount);
	}
}
