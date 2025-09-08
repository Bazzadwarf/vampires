// Louis Hobbs | 2024-2025


#include "UpgradeButtonWidget.h"

#include "LevelUpWidget.h"
#include "UpgradeButtonDataObject.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "vampires/Weapon.h"
#include "UObject/UObjectBase.h"
#include "vampires/GoldComponent.h"
#include "vampires/HealthComponent.h"
#include "vampires/WeaponInventoryComponent.h"

void UUpgradeButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();

	OnFocused.AddUniqueDynamic(this, &UUpgradeButtonWidget::SetFocusInParent);
}

void UUpgradeButtonWidget::SetData(UUpgradeButtonDataObject* ListItemObject)
{
	if (UUpgradeButtonDataObject* Item = Cast<UUpgradeButtonDataObject>(ListItemObject))
	{
		TextBlock->SetText(Item->WeaponName);
		ButtonText = Item->WeaponName;
		DescriptionTextBlock->SetText(Item->WeaponDescription);
		WeaponIcon->SetBrushFromTexture(Item->WeaponIcon);
		Parent = Item->Parent;

		if (Item->WeaponInstance != nullptr)
		{
			UpgradeType = Upgrade;
			WeaponInstance = Item->WeaponInstance;
		}
		else if (Item->WeaponTemplate != nullptr)
		{
			UpgradeType = NewWeapon;
			WeaponTemplate = Item->WeaponTemplate;
		}
		else if (Item->WeaponName.ToString() == "Health")
		{
			UpgradeType = Health;
		}
		else if (Item->WeaponName.ToString() == "Gold")
		{
			UpgradeType = Gold;
		}
	}


	switch (UpgradeType)
	{
	case Upgrade:
		UpgradeTypeIcon->SetBrushFromTexture(UpgradeIcon);
		break;
	case NewWeapon:
		UpgradeTypeIcon->SetBrushFromTexture(NewWeaponIcon);
		break;
	case Health:
		UpgradeTypeIcon->SetBrushFromTexture(HealthIcon);
		break;
	case Gold:
		UpgradeTypeIcon->SetBrushFromTexture(GoldIcon);
		break;
	default: ;
	}
}

void UUpgradeButtonWidget::OnButtonClicked()
{
	Super::OnButtonClicked();

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	switch (UpgradeType)
	{
	case Upgrade:
		WeaponInstance->UpgradeWeapon();
		break;

	case NewWeapon:
		if (UWeaponInventoryComponent* Inventory = PlayerController->GetPawn()->GetComponentByClass<
			UWeaponInventoryComponent>())
		{
			Inventory->AddWeaponToInventory(WeaponTemplate);
			Inventory->ObtainableWeapons.Remove(WeaponTemplate);
		}
		break;

	case Health:
		if (PlayerController)
		{
			if (UHealthComponent* HealthComponent = PlayerController->GetPawn()->GetComponentByClass<
				UHealthComponent>())
			{
				HealthComponent->RecoverHealth(HealthComponent->GetMaxHealth() / 10.0f);
			}
		}
		break;

	case Gold:
		if (PlayerController)
		{
			if (UGoldComponent* GoldComponent = PlayerController->GetPawn()->GetComponentByClass<UGoldComponent>())
			{
				GoldComponent->IncrementGold(10);
			}
		}
		break;

	default:
		break;
	}

	if (Parent)
	{
		Parent->RemoveFromParent();

		if (PlayerController)
		{
			UWidgetBlueprintLibrary::SetInputMode_GameOnly(PlayerController);
			PlayerController->bShowMouseCursor = false;
			PlayerController->SetPause(false);
		}

		Parent->SetIsFocusable(false);
	}
}

void UUpgradeButtonWidget::SetFocusInParent(FFocusEvent InFocusEvent)
{
	if (ULevelUpWidget* LevelUpMenu = Cast<ULevelUpWidget>(Parent))
	{
		LevelUpMenu->SetCurrentFocus(this);
	}
}
