// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "HUDWidget.generated.h"

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
	
};
