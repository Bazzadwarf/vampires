// Louis Hobbs | 2024-2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "VampirePlayerController.generated.h"

class ULevelUpWidget;
class UPauseWidget;
struct FInputActionValue;
class UInputAction;
class UHUDWidget;
/**
 * 
 */
UCLASS(Abstract)
class VAMPIRES_API AVampirePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	// UI
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UHUDWidget> PlayerHUD = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UPauseWidget> PauseUI = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ULevelUpWidget> LevelUpUI = nullptr;

	// Inputs	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UInputAction* MovementAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UInputAction* PauseAction;

private:

	TObjectPtr<UHUDWidget> currentPlayerHUD = nullptr;

	TObjectPtr<UPauseWidget> currentPauseUI = nullptr;
	
	TObjectPtr<ULevelUpWidget> currentLevelUpUI = nullptr;

	FTimerHandle pawnLifeTimeHandle;

protected:
	virtual void OnPossess(APawn* aPawn) override;

	virtual void OnUnPossess() override;

	virtual void SetupInputComponent() override;

	UFUNCTION()
	void Move(const FInputActionValue& MovementInput);

	UFUNCTION()
	void OnPause(const FInputActionValue& PauseInput);

	UFUNCTION()
	void UpdatePlayerEXPHUD(int exp, float currentLevelPercent);

	UFUNCTION()
	void ShowLevelUpScreen(int level);

	UFUNCTION()
	void UpdatePlayerLevelHUD(int level);

	UFUNCTION()
	void UpdateTimerHUD();

	UFUNCTION()
	void UpdateKillCountHUD(int killCount);
};
