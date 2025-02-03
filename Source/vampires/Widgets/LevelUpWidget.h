// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LevelUpWidget.generated.h"

class UUpgradeButtonDataObject;
class UListView;
class UButton;
/**
 * 
 */
UCLASS(Blueprintable)
class VAMPIRES_API ULevelUpWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UButton* ResumeButton;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UListView* UpgradesListView;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<UUpgradeButtonDataObject>> UpgradeItems;
	
	virtual void NativeConstruct() override;
	
private:

	
	UFUNCTION()
	void ResumeButtonClicked();
};
