// Louis Hobbs | 2024-2025


#include "VampirePlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EXPComponent.h"
#include "GoldComponent.h"
#include "Inputable.h"
#include "VampireGameMode.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/HUDWidget.h"
#include "Widgets/LevelUpWidget.h"
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
			expComponent->OnEXPLevelUp.AddUniqueDynamic(this, &AVampirePlayerController::ShowLevelUpScreen);
			UpdatePlayerEXPHUD(expComponent->GetCurrentEXP(), expComponent->GetCurrentLevelPercent());
			UpdatePlayerLevelHUD(expComponent->GetCurrentLevel());
		}

		if (UGoldComponent* goldComponent = aPawn->GetComponentByClass<UGoldComponent>())
		{
			goldComponent->OnGoldGained.AddUniqueDynamic(this, &AVampirePlayerController::UpdateGoldCountHUD);
			UpdateGoldCountHUD(goldComponent->GetCurrentGold());
		}

		if (AVampireGameMode* gamemode = Cast<AVampireGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
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
	
	if (PauseUI)
	{
		if (SetPause(true))
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

void AVampirePlayerController::ShowLevelUpScreen(int level)
{
	APawn* pawn = GetPawn();
	if (!pawn)
	{
		return;
	}
	
	UEXPComponent* expComponent = pawn->GetComponentByClass<UEXPComponent>();
	if (!expComponent || expComponent->GetCurrentLevel() == 0)
	{
		return;
	}
	
	if (LevelUpUI)
	{
		if (SetPause(true))
		{
			currentLevelUpUI = CreateWidget<ULevelUpWidget, AVampirePlayerController*>(this, LevelUpUI.Get());
			if (currentLevelUpUI)
			{
				currentLevelUpUI->AddToViewport();
				UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(this, currentLevelUpUI, EMouseLockMode::LockInFullscreen);
				bShowMouseCursor = true;
			}
		}		
	}
}

void AVampirePlayerController::UpdatePlayerLevelHUD(int level)
{
	if (currentPlayerHUD)
	{
		currentPlayerHUD->UpdateLevelBlock(level);
	}
}

void AVampirePlayerController::UpdateTimerHUD(float deltaTime)
{
	if (currentPlayerHUD)
	{
		currentPlayerHUD->UpdateTimerBlock(deltaTime);
	}
}

void AVampirePlayerController::UpdateKillCountHUD(int killCount)
{
	if (currentPlayerHUD)
	{
		currentPlayerHUD->UpdateKillBlock(killCount);
	}
}

void AVampirePlayerController::UpdateGoldCountHUD(int goldCount)
{
	if (currentPlayerHUD)
	{
		currentPlayerHUD->UpdateGoldBlock(goldCount);
	}
}

void AVampirePlayerController::UpdateTimerHUDElement_Implementation(float deltaTime)
{
	if (currentPlayerHUD)
	{
		currentPlayerHUD->UpdateTimerBlock(deltaTime);
	}
}
