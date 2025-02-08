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
	
public:
	
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
	
	UFUNCTION()
	void UpdateEXPBar(float currentLevelPercent);

	UFUNCTION()
	void UpdateLevelBlock(int level);

	UFUNCTION()
	void UpdateTimerBlock(APawn* pawn);

	UFUNCTION()
	void UpdateKillBlock(int killCount);

	UFUNCTION()
	void UpdateGoldBlock(int goldCount);
	
};
