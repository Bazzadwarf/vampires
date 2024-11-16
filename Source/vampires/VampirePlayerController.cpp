// Fill out your copyright notice in the Description page of Project Settings.


#include "VampirePlayerController.h"

#include "EXPComponent.h"
#include "HealthComponent.h"
#include "Blueprint/UserWidget.h"
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
			UpdatePlayerEXPHUD(expComponent->GetCurrentEXP(), expComponent->GetCurrentLevelPercent());
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
