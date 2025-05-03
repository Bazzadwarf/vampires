// Louis Hobbs | 2024-2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Interfaces/Playerable.h"
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
class VAMPIRES_API AVampirePlayerController : public APlayerController, public IPlayerable
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
	TObjectPtr<UInputAction> MovementAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UInputAction> PauseAction;

private:

	UPROPERTY()
	TObjectPtr<UHUDWidget> currentPlayerHUD = nullptr;

	UPROPERTY()
	TObjectPtr<UPauseWidget> currentPauseUI = nullptr;

	UPROPERTY()
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

	UFUNCTION(BlueprintCallable)
	void UpdateTimerHUD(float deltaTime);

	UFUNCTION()
	void UpdateKillCountHUD(int killCount);

	UFUNCTION()
	void UpdateGoldCountHUD(int goldCount);

	virtual void UpdateTimerHUDElement_Implementation(float deltaTime) override;
};
