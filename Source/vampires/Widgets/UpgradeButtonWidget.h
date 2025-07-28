// Louis Hobbs | 2024-2025

#pragma once

#include "CoreMinimal.h"
#include "VampireInteractiveWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "UpgradeButtonWidget.generated.h"

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
class VAMPIRES_API UUpgradeButtonWidget : public UVampireInteractiveWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

protected:
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
	TObjectPtr<UTexture2D> HealthIcon;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UTexture2D> GoldIcon;

	UPROPERTY(EditDefaultsOnly)
	TEnumAsByte<EUpgradeType> UpgradeType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AWeapon> WeaponTemplate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<AWeapon> WeaponInstance;

	UPROPERTY()
	TObjectPtr<UUserWidget> Parent;

private:
	UPROPERTY(meta=(BindWidget))
	UImage* UpgradeTypeIcon;

protected:
	virtual void NativeConstruct() override;

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

private:
	UFUNCTION()
	virtual void OnClicked();

	UFUNCTION()
	void OnHoveredDelegate() { SetTextBlockHovered(WeaponNameTextBlock); SetTextBlockHovered(DescriptionTextBlock); }

	UFUNCTION()
	void OnUnhoveredDelegate() { SetTextBlockUnhovered(WeaponNameTextBlock); SetTextBlockUnhovered(DescriptionTextBlock); }
};
