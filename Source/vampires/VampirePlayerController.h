// Louis Hobbs | 2024-2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Interfaces/Playerable.h"
#include "VampirePlayerController.generated.h"

struct FDamageInfo;
class UGameOverWidget;
class ULevelUpWidget;
class UPauseWidget;
struct FInputActionValue;
class UInputAction;
class UHUDWidget;

/**
 * 
 */
UCLASS(Abstract)
class VAMPIRES_API AVampirePlayerController : public APlayerController, public IPlayerable
{
	GENERATED_BODY()

public:
	// UI
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UHUDWidget> PlayerHUD = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UPauseWidget> PauseUI = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<ULevelUpWidget> LevelUpUI = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UGameOverWidget> GameOverUI = nullptr;

	// Inputs	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UInputAction> MovementAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UInputAction> PauseAction;

private:
	UPROPERTY()
	TObjectPtr<UHUDWidget> CurrentPlayerHUD = nullptr;

	UPROPERTY()
	TObjectPtr<UPauseWidget> CurrentPauseUI = nullptr;

	UPROPERTY()
	TObjectPtr<ULevelUpWidget> CurrentLevelUpUI = nullptr;
	
	UPROPERTY()
	TObjectPtr<UGameOverWidget> CurrentGameOverUI = nullptr;

	FTimerHandle PawnLifeTimeHandle;

public:
	UFUNCTION()
	void OnDeath(FDamageInfo DamageInfo);

protected:
	virtual void OnPossess(APawn* aPawn) override;

	virtual void OnUnPossess() override;

	virtual void SetupInputComponent() override;

	UFUNCTION()
	void Move(const FInputActionValue& MovementInput);

	UFUNCTION()
	void OnPause(const FInputActionValue& PauseInput);


	UFUNCTION()
	void UpdatePlayerEXPHUD(int Exp, float CurrentLevelPercent);

	UFUNCTION()
	void ShowLevelUpScreen(int Level);

	UFUNCTION()
	void UpdatePlayerLevelHUD(int Level);

	UFUNCTION(BlueprintCallable)
	void UpdateTimerHUD(float DeltaTime);

	UFUNCTION()
	void UpdateKillCountHUD(int KillCount);

	UFUNCTION()
	void UpdateGoldCountHUD(int GoldCount);

	virtual void UpdateTimerHUDElement_Implementation(float DeltaTime) override;
};
