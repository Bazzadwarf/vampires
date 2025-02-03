// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "UpgradeButtonWidget.generated.h"

UENUM(BlueprintType)
enum EUpgradeType
{
	Upgrade,
	NewWeapon
};

class UTextBlock;
class UImage;
class UButton;

/**
 * 
 */
UCLASS()
class VAMPIRES_API UUpgradeButtonWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	TObjectPtr<UButton> Body;

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	TObjectPtr<UImage> WeaponIcon;
	
	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	TObjectPtr<UTextBlock> WeaponNameTextBlock;

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	TObjectPtr<UTextBlock> DescriptionTextBlock;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UTexture2D> UpgradeIcon;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UTexture2D> NewWeaponIcon;

	UPROPERTY(EditDefaultsOnly)
	TEnumAsByte<EUpgradeType> UpgradeType;

private:
	UPROPERTY(meta=(BindWidget))
	UImage* UpgradeTypeIcon;
	
protected:
	virtual void NativeConstruct() override;

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	
private:
	UFUNCTION()
	virtual void OnClicked();
};
