// Fill out your copyright notice in the Description page of Project Settings.

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

	void Init();
	
	UFUNCTION()
	void UpdateEXPBar(float currentLevelPercent);

	UFUNCTION()
	void UpdateLevelBlock();

	UFUNCTION()
	void UpdateTimerBlock();
	
};
