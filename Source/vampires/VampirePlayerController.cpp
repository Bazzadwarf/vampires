// Louis Hobbs | 2024-2025


#include "VampirePlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EXPComponent.h"
#include "GoldComponent.h"
#include "Inputable.h"
#include "VampireGameInstance.h"
#include "VampireGameMode.h"
#include "Weapon.h"
#include "WeaponInventoryComponent.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/GameOverWidget.h"
#include "Widgets/HUDWidget.h"
#include "Widgets/LevelUpWidget.h"
#include "Widgets/PauseWidget.h"

void AVampirePlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		GetLocalPlayer()))
	{
		if (UKismetSystemLibrary::DoesImplementInterface(aPawn, UInputable::StaticClass()))
		{
			Subsystem->AddMappingContext(IInputable::Execute_Input_GetInputMappingContext(aPawn), 0);
		}
	}

	if (PlayerHUD)
	{
		CurrentPlayerHUD = CreateWidget<UHUDWidget, AVampirePlayerController*>(this, PlayerHUD.Get());

		if (UEXPComponent* ExpComponent = aPawn->GetComponentByClass<UEXPComponent>())
		{
			ExpComponent->OnEXPGained.AddUniqueDynamic(this, &AVampirePlayerController::UpdatePlayerEXPHUD);
			ExpComponent->OnEXPLevelUp.AddUniqueDynamic(this, &AVampirePlayerController::UpdatePlayerLevelHUD);
			ExpComponent->OnEXPLevelUp.AddUniqueDynamic(this, &AVampirePlayerController::ShowLevelUpScreen);
			UpdatePlayerEXPHUD(ExpComponent->GetCurrentEXP(), ExpComponent->GetCurrentLevelPercent());
			UpdatePlayerLevelHUD(ExpComponent->GetCurrentLevel());
		}

		if (UGoldComponent* GoldComponent = aPawn->GetComponentByClass<UGoldComponent>())
		{
			GoldComponent->OnGoldGained.AddUniqueDynamic(this, &AVampirePlayerController::UpdateGoldCountHUD);
			UpdateGoldCountHUD(GoldComponent->GetCurrentGold());
		}

		if (AVampireGameMode* Gamemode = Cast<AVampireGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
		{
			Gamemode->OnEnemyDeathCountIncrementDelegate.
			          AddDynamic(this, &AVampirePlayerController::UpdateKillCountHUD);
			UpdateKillCountHUD(Gamemode->GetEnemyDeathCount());
		}

		if (CurrentPlayerHUD)
		{
			CurrentPlayerHUD->AddToViewport();
		}
	}

	if (UVampireGameInstance* GameInstance = Cast<UVampireGameInstance>(GetGameInstance()))
	{
		UWeaponInventoryComponent* WeaponInventoryComponent = aPawn->GetComponentByClass<
			UWeaponInventoryComponent>();

		if (WeaponInventoryComponent && GameInstance->StarterWeapon)
		{
			WeaponInventoryComponent->InitialInventory.Add(GameInstance->StarterWeapon);
		}
	}
}

void AVampirePlayerController::OnUnPossess()
{
	Super::OnUnPossess();

	GetWorld()->GetTimerManager().ClearTimer(PawnLifeTimeHandle);
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
	FVector2D Movement = MovementInput.Get<FVector2D>();

	if (APawn* pawn = GetPawn())
	{
		if (UKismetSystemLibrary::DoesImplementInterface(pawn, UInputable::StaticClass()))
		{
			IInputable::Execute_Input_Move(pawn, Movement);
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
			CurrentPauseUI = CreateWidget<UPauseWidget, AVampirePlayerController*>(this, PauseUI.Get());
			if (CurrentPauseUI)
			{
				CurrentPauseUI->AddToViewport();
				UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(this, CurrentPauseUI, EMouseLockMode::LockInFullscreen);
				bShowMouseCursor = true;
			}
		}
	}
}

void AVampirePlayerController::OnDeath(FDamageInfo DamageInfo)
{
	if (GameOverUI)
	{
		if (CurrentPlayerHUD) { CurrentPlayerHUD->RemoveFromParent(); }
		if (CurrentLevelUpUI) { CurrentLevelUpUI->RemoveFromParent(); }
		if (CurrentPauseUI) { CurrentPauseUI->RemoveFromParent(); }

		CurrentGameOverUI = CreateWidget<UGameOverWidget, AVampirePlayerController*>(this, GameOverUI.Get());
		if (CurrentGameOverUI)
		{
			CurrentGameOverUI->AddToViewport();
			UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(this, CurrentPauseUI, EMouseLockMode::LockInFullscreen);
			bShowMouseCursor = true;

			int Level = -1;
			if (UEXPComponent* EXPComponent = GetPawn()->GetComponentByClass<UEXPComponent>())
			{
				Level = EXPComponent->GetCurrentLevel();
			}

			int Kills = -1;
			if (AVampireGameMode* GameMode = Cast<AVampireGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
			{
				Kills = GameMode->GetEnemyDeathCount();
			}

			int Gold = -1;
			if (UGoldComponent* GoldComponent = GetPawn()->GetComponentByClass<UGoldComponent>())
			{
				Gold = GoldComponent->GetCurrentGold();
			}

			CurrentGameOverUI->SetGameInfo(Level, ElapsedTime, Kills, Gold);
		}
	}
}

void AVampirePlayerController::UpdatePlayerEXPHUD(int Exp, float CurrentLevelPercent)
{
	if (CurrentPlayerHUD)
	{
		CurrentPlayerHUD->UpdateEXPBar(CurrentLevelPercent);
	}
}

void AVampirePlayerController::ShowLevelUpScreen(int Level)
{
	APawn* pawn = GetPawn();
	if (!pawn)
	{
		return;
	}

	UEXPComponent* ExpComponent = pawn->GetComponentByClass<UEXPComponent>();
	if (!ExpComponent || ExpComponent->GetCurrentLevel() == 0)
	{
		return;
	}

	if (LevelUpUI)
	{
		if (SetPause(true))
		{
			CurrentLevelUpUI = CreateWidget<ULevelUpWidget, AVampirePlayerController*>(this, LevelUpUI.Get());
			if (CurrentLevelUpUI)
			{
				CurrentLevelUpUI->AddToViewport();
				UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(this, CurrentLevelUpUI,
				                                               EMouseLockMode::LockInFullscreen);
				bShowMouseCursor = true;
			}
		}
	}
}

void AVampirePlayerController::UpdatePlayerLevelHUD(int Level)
{
	if (CurrentPlayerHUD)
	{
		CurrentPlayerHUD->UpdateLevelBlock(Level);
	}
}

void AVampirePlayerController::UpdateTimerHUD(float DeltaTime)
{
	if (CurrentPlayerHUD)
	{
		CurrentPlayerHUD->UpdateTimerBlock(DeltaTime);
	}
}

void AVampirePlayerController::UpdateKillCountHUD(int KillCount)
{
	if (CurrentPlayerHUD)
	{
		CurrentPlayerHUD->UpdateKillBlock(KillCount);
	}
}

void AVampirePlayerController::UpdateGoldCountHUD(int GoldCount)
{
	if (CurrentPlayerHUD)
	{
		CurrentPlayerHUD->UpdateGoldBlock(GoldCount);
	}
}

void AVampirePlayerController::UpdateTimerHUDElement_Implementation(float DeltaTime)
{
	ElapsedTime = DeltaTime;

	if (CurrentPlayerHUD)
	{
		CurrentPlayerHUD->UpdateTimerBlock(DeltaTime);
	}
}
