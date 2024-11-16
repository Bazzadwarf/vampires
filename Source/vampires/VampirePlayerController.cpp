// Fill out your copyright notice in the Description page of Project Settings.


#include "VampirePlayerController.h"

#include "EXPComponent.h"
#include "Blueprint/UserWidget.h"
#include "Widgets/HUDWidget.h"

void AVampirePlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	if (PlayerHUD)
	{
		currentPlayerHUD = CreateWidget<UHUDWidget, AVampirePlayerController*>(this, PlayerHUD.Get());

		if (currentPlayerHUD)
		{
			currentPlayerHUD->AddToViewport();
		}
	}
}

