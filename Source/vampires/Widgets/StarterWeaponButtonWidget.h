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

protected:
	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	TObjectPtr<UButton> Body;

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	TObjectPtr<UImage> WeaponIcon;

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	TObjectPtr<UTextBlock> WeaponNameTextBlock;

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	TObjectPtr<UTextBlock> DescriptionTextBlock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AWeapon> WeaponTemplate;

	UPROPERTY()
	TObjectPtr<UUserWidget> Parent;

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
