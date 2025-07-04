// Louis Hobbs | 2024-2025


#include "UpgradeButtonWidget.h"

#include "UpgradeButtonDataObject.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Button.h"
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

		if (Body)
		{
			Body->OnClicked.AddUniqueDynamic(this, &UUpgradeButtonWidget::OnClicked);

			Body->OnHovered.AddUniqueDynamic(this, &UUpgradeButtonWidget::PlayHoveredSound);
			Body->OnHovered.AddUniqueDynamic(this, &UUpgradeButtonWidget::OnHoveredDelegate);

			Body->OnUnhovered.AddUniqueDynamic(this, &UUpgradeButtonWidget::OnUnhoveredDelegate);
			Body->OnUnhovered.AddUniqueDynamic(this, &UUpgradeButtonWidget::PlayUnhoveredSound);
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

void UUpgradeButtonWidget::OnClicked()
{
	APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	switch (UpgradeType)
	{
	case Upgrade:
		WeaponInstance->UpgradeWeapon();
		break;

	case NewWeapon:
		if (UWeaponInventoryComponent* Inventory = playerController->GetPawn()->GetComponentByClass<
			UWeaponInventoryComponent>())
		{
			Inventory->AddWeaponToInventory(WeaponTemplate);
			Inventory->obtainableWeapons.Remove(WeaponTemplate);
		}
		break;

	case Health:
		if (playerController)
		{
			if (UHealthComponent* healthComponent = playerController->GetPawn()->GetComponentByClass<
				UHealthComponent>())
			{
				healthComponent->RecoverHealth(healthComponent->GetMaxHealth() / 10.0f);
			}
		}
		break;

	case Gold:
		if (playerController)
		{
			if (UGoldComponent* goldComponent = playerController->GetPawn()->GetComponentByClass<UGoldComponent>())
			{
				goldComponent->IncrementGold(10);
			}
		}
		break;

	default:
		break;
	}

	if (Parent)
	{
		Parent->RemoveFromParent();

		if (playerController)
		{
			UWidgetBlueprintLibrary::SetInputMode_GameOnly(playerController);
			playerController->bShowMouseCursor = false;
			playerController->SetPause(false);
		}

		Parent->SetIsFocusable(false);
	}
}
