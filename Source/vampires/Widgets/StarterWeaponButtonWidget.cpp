// Louis Hobbs | 2024-2025


#include "StarterWeaponButtonWidget.h"

#include "StarterWeaponButtonDataObject.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UStarterWeaponButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UStarterWeaponButtonWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UStarterWeaponButtonDataObject* Item = Cast<UStarterWeaponButtonDataObject>(ListItemObject);
	
	if (Item)
	{
		WeaponNameTextBlock->SetText(Item->WeaponName);
		DescriptionTextBlock->SetText(Item->Description);
		WeaponIcon->SetBrushFromTexture(Item->WeaponIcon);
		Parent = Item->Parent;
		WeaponTemplate = Item->WeaponTemplate;

		if (Body)
		{
			Body->OnClicked.AddUniqueDynamic(this, &UStarterWeaponButtonWidget::OnClicked);
		}
	}
}

void UStarterWeaponButtonWidget::OnClicked()
{
}
