// Louis Hobbs | 2024-2025

#pragma once

#include "CoreMinimal.h"
#include "CustomButton.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "StarterWeaponButtonWidget.generated.h"

class UStarterWeaponButtonDataObject;
class AWeapon;
class UTextBlock;
class UImage;

/**
 * 
 */
UCLASS()
class VAMPIRES_API UStarterWeaponButtonWidget : public UCustomButton, public IUserObjectListEntry
{
	GENERATED_BODY()

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> WeaponIcon;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> DescriptionTextBlock;

	UPROPERTY()
	TSubclassOf<AWeapon> WeaponTemplate;

	UPROPERTY()
	TObjectPtr<UUserWidget> Parent;

protected:
	virtual void NativeConstruct() override;

public:
	void SetData(UStarterWeaponButtonDataObject* ListItemObject);

private:
	virtual void OnButtonClicked() override;

	UFUNCTION()
	void SetFocusInParent(FFocusEvent InFocusEvent);
};
