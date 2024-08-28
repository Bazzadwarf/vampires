// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "vampires/VampireCharacter.h"
#include "HealthbarWidget.generated.h"

/**
 * 
 */
UCLASS()
class VAMPIRES_API UHealthbarWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* HealthBar;

	virtual void NativeConstruct() override;
	
private:
	UFUNCTION()
	void UpdateHealthBar();
};
