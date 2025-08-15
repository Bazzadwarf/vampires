// Louis Hobbs | 2024-2025

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"

class UTextBlock;
class UProgressBar;
/**
 * 
 */
UCLASS()
class VAMPIRES_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	UProgressBar* EXPbar;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* LevelBlock;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TimerBLock;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* KillBLock;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* GoldBLock;

public:
	UFUNCTION()
	void UpdateEXPBar(float CurrentLevelPercent);

	UFUNCTION()
	void UpdateLevelBlock(int Level);

	UFUNCTION()
	void UpdateTimerBlock(float DeltaTime);

	UFUNCTION()
	void UpdateKillBlock(int KillCount);

	UFUNCTION()
	void UpdateGoldBlock(int GoldCount);
};
