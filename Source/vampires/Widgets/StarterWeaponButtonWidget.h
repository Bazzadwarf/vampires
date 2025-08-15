// Louis Hobbs | 2024-2025

#pragma once

#include "CoreMinimal.h"
#include "VampireInteractiveWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "StarterWeaponButtonWidget.generated.h"

class AWeapon;
class UTextBlock;
class UImage;
class UButton;
/**
 * 
 */
UCLASS()
class VAMPIRES_API UStarterWeaponButtonWidget : public UVampireInteractiveWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> Body;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> WeaponIcon;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> WeaponNameTextBlock;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> DescriptionTextBlock;

	UPROPERTY()
	TSubclassOf<AWeapon> WeaponTemplate;

	UPROPERTY()
	TObjectPtr<UUserWidget> Parent;

	virtual void NativeConstruct() override;

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	UFUNCTION()
	virtual void OnClicked();

	UFUNCTION()
	void OnHoveredDelegate();

	UFUNCTION()
	void OnUnhoveredDelegate();
};
