// Fill out your copyright notice in the Description page of Project Settings.


#include "UpgradeButtonWidget.h"

#include "UpgradeButtonDataObject.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UUpgradeButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (Body)
	{
		Body->OnClicked.AddUniqueDynamic(this, &UUpgradeButtonWidget::OnClicked);
	}
}

void UUpgradeButtonWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UUpgradeButtonDataObject* Item = Cast<UUpgradeButtonDataObject>(ListItemObject);

	if (Item)
	{
		WeaponNameTextBlock->SetText(Item->WeaponName);
		DescriptionTextBlock->SetText(Item->Description);
		WeaponIcon->SetBrushFromTexture(Item->WeaponIcon);
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
}
