// Fill out your copyright notice in the Description page of Project Settings.


#include "VampirePlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EXPComponent.h"
#include "Inputable.h"
#include "VampireGameMode.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/HUDWidget.h"
#include "Widgets/PauseWidget.h"

void AVampirePlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	if (UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (UKismetSystemLibrary::DoesImplementInterface(aPawn, UInputable::StaticClass()))
		{
			subsystem->AddMappingContext(IInputable::Execute_Input_GetInputMappingContext(aPawn), 0);
		}
	}
	
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

		if (AVampireGameMode* gamemode = Cast<AVampireGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
		{
			gamemode->OnEnemyDeathCountIncrementDelegate.AddDynamic(this, &AVampirePlayerController::UpdateKillCountHUD);
			UpdateKillCountHUD(gamemode->GetEnemyDeathCount());
		}

		GetWorld()->GetTimerManager().SetTimer(pawnLifeTimeHandle, this, &AVampirePlayerController::UpdateTimerHUD, 1.0f, true,0.f);
		
		if (currentPlayerHUD)
		{
			currentPlayerHUD->AddToViewport();
		}
	}
}

void AVampirePlayerController::OnUnPossess()
{
	Super::OnUnPossess();

	GetWorld()->GetTimerManager().ClearTimer(pawnLifeTimeHandle);
}

void AVampirePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EIP = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EIP->BindAction(MovementAction, ETriggerEvent::Triggered, this, &AVampirePlayerController::Move);
		EIP->BindAction(PauseAction, ETriggerEvent::Triggered, this, &AVampirePlayerController::OnPause);
	}
}

void AVampirePlayerController::Move(const FInputActionValue& MovementInput)
{
	FVector2D movement = MovementInput.Get<FVector2D>();

	if (APawn* pawn = GetPawn())
	{
		if (UKismetSystemLibrary::DoesImplementInterface(pawn, UInputable::StaticClass()))
		{
			IInputable::Execute_Input_Move(pawn, movement);
		}
	}
}

void AVampirePlayerController::OnPause(const FInputActionValue& PauseInput)
{
	if (APawn* pawn = GetPawn())
	{
		if (UKismetSystemLibrary::DoesImplementInterface(pawn, UInputable::StaticClass()))
		{
			IInputable::Execute_Input_Pause(pawn);
		}
	}
	
	if (SetPause(true))
	{
		if (PauseUI)
		{
			currentPauseUI = CreateWidget<UPauseWidget, AVampirePlayerController*>(this, PauseUI.Get());
			if (currentPauseUI)
			{
				currentPauseUI->AddToViewport();
				UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(this, currentPauseUI, EMouseLockMode::LockInFullscreen);
				bShowMouseCursor = true;
			}
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

void AVampirePlayerController::UpdateTimerHUD()
{
	if (currentPlayerHUD)
	{
		currentPlayerHUD->UpdateTimerBlock(GetPawn());
	}
}

void AVampirePlayerController::UpdateKillCountHUD(int killCount)
{
	if (currentPlayerHUD)
	{
		currentPlayerHUD->UpdateKillBlock(killCount);
	}
}
