// Fill out your copyright notice in the Description page of Project Settings.


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
		// TODO: Spawn weapon
		break;
	case Health:
		if (playerController)
		{
			if (UHealthComponent* healthComponent = playerController->GetComponentByClass<UHealthComponent>())
			{
				healthComponent->RecoverHealth(healthComponent->GetMaxHealth() / 10.0f);
			}
		}
		break;
	case Gold:
		if (playerController)
		{
			if (UGoldComponent* goldComponent = playerController->GetComponentByClass<UGoldComponent>())
			{
				goldComponent->IncrementGold(10);
			}
		}
		break;
	default: ;
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
