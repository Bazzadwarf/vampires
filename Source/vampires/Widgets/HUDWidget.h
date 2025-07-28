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

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* EXPbar;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* LevelBlock;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* TimerBLock;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* KillBLock;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* GoldBLock;

	void Init();

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
