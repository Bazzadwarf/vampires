// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LevelUpWidget.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class VAMPIRES_API ULevelUpWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UButton* ResumeButton;

	virtual void NativeConstruct() override;

private:

	
	UFUNCTION()
	void ResumeButtonClicked();
};
