// Fill out your copyright notice in the Description page of Project Settings.


#include "UpgradeButtonWidget.h"

#include "UpgradeButtonDataObject.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "vampires/Weapon.h"
#include "UObject/UObjectBase.h"

void UUpgradeButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UUpgradeButtonWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UUpgradeButtonDataObject* Item = Cast<UUpgradeButtonDataObject>(ListItemObject);

	if (Item)
	{
		WeaponNameTextBlock->SetText(Item->WeaponName);
		DescriptionTextBlock->SetText(Item->Description);
		WeaponIcon->SetBrushFromTexture(Item->WeaponIcon);
		Parent = Item->Parent;

		if (Item->WeaponInstance != nullptr)
		{
			UpgradeType = EUpgradeType::Upgrade;
			WeaponInstance = Item->WeaponInstance;
		}
		else if (Item->WeaponTemplate != nullptr)
		{
			UpgradeType = EUpgradeType::NewWeapon;
			WeaponTemplate = Item->WeaponTemplate;
		}


		if (Body)
		{
			Body->OnClicked.AddUniqueDynamic(this, &UUpgradeButtonWidget::OnClicked);
		}
	}
	
	
	switch (UpgradeType) {
	case Upgrade:
		UpgradeTypeIcon->SetBrushFromTexture(UpgradeIcon);
		break;
	case NewWeapon:
		UpgradeTypeIcon->SetBrushFromTexture(NewWeaponIcon);
		break;
	default: ;
	}
}

void UUpgradeButtonWidget::OnClicked()
{
	switch (UpgradeType) {
	case Upgrade:
		WeaponInstance->UpgradeWeapon();
		break;
	case NewWeapon:
		// TODO: Spawn weapon
		break;
	default: ;
	}

	if (Parent)
	{
		Parent->RemoveFromParent();

		if (APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
		{
			UWidgetBlueprintLibrary::SetInputMode_GameOnly(playerController);
			playerController->bShowMouseCursor = false;
			playerController->SetPause(false);
		}

		Parent->SetIsFocusable(false);
	}
}
