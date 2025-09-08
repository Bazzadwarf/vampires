// Louis Hobbs | 2024-2025

#pragma once

#include "CoreMinimal.h"
#include "CustomButton.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "UpgradeButtonWidget.generated.h"

class UUpgradeButtonDataObject;
class AWeapon;

UENUM(BlueprintType)
enum EUpgradeType
{
	Upgrade,
	NewWeapon,
	Health,
	Gold
};

class UTextBlock;
class UImage;
class UButton;

/**
 * 
 */
UCLASS()
class VAMPIRES_API UUpgradeButtonWidget : public UCustomButton, public IUserObjectListEntry
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UTexture2D> UpgradeIcon;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UTexture2D> NewWeaponIcon;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UTexture2D> HealthIcon;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UTexture2D> GoldIcon;

private:
	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	TObjectPtr<UImage> WeaponIcon;

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	TObjectPtr<UTextBlock> DescriptionTextBlock;

	UPROPERTY(EditDefaultsOnly)
	TEnumAsByte<EUpgradeType> UpgradeType;

	UPROPERTY()
	TSubclassOf<AWeapon> WeaponTemplate;

	UPROPERTY()
	TObjectPtr<AWeapon> WeaponInstance;

	UPROPERTY()
	TObjectPtr<UUserWidget> Parent;

	UPROPERTY(meta=(BindWidget))
	UImage* UpgradeTypeIcon;

protected:
	virtual void NativeConstruct() override;

public:
	virtual void SetData(UUpgradeButtonDataObject* ListItemObject);

private:
	virtual void OnButtonClicked() override;

	UFUNCTION()
	void SetFocusInParent(FFocusEvent InFocusEvent);
};
