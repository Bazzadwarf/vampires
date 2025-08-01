﻿// Louis Hobbs | 2024-2025


#include "LevelUpWidget.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Button.h"
#include "Components/ListView.h"
#include "Kismet/GameplayStatics.h"
#include "UpgradeButtonDataObject.h"
#include "GameFramework/Character.h"
#include "vampires/VampireCharacter.h"
#include "vampires/Weapon.h"
#include "vampires/WeaponInventoryComponent.h"

void ULevelUpWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ResumeButton)
	{
		ResumeButton->OnClicked.AddUniqueDynamic(this, &ULevelUpWidget::ResumeButtonClicked);
	}

	if (UpgradesListView)
	{
		ACharacter* Player = Cast<AVampireCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (!Player)
		{
			return;
		}

		UWeaponInventoryComponent* InventoryComponent = Player->GetComponentByClass<UWeaponInventoryComponent>();
		if (!InventoryComponent)
		{
			return;
		}

		UpgradesListView->ClearListItems();
		TArray<AWeapon*> Inventory = InventoryComponent->GetInventory();

		// Get list of weapons that the player owns that can be upgraded
		TArray<UUpgradeButtonDataObject*> UpgradeItems;
		for (AWeapon* Weapon : Inventory)
		{
			if (Weapon->GetWeaponLevel() < Weapon->GetUpgradeDescriptions().Num())
			{
				UUpgradeButtonDataObject* Temp = NewObject<UUpgradeButtonDataObject>(this);
				Temp->SetData(Weapon, this);
				UpgradeItems.Add(Temp);
			}
		}

		// Get list of weapons that the player can still obtain 
		TArray<TSubclassOf<AWeapon>> ObtainableWeapons = InventoryComponent->ObtainableWeapons;
		for (TSubclassOf<AWeapon> Weapon : ObtainableWeapons)
		{
			UUpgradeButtonDataObject* Temp = NewObject<UUpgradeButtonDataObject>(this);
			Temp->SetData(Weapon, this);
			UpgradeItems.Add(Temp);
		}

		// If no valid options exist, populate list with default options
		if (UpgradeItems.Num() == 0)
		{
			UUpgradeButtonDataObject* TempHealth = NewObject<UUpgradeButtonDataObject>(this);
			TempHealth->SetData(FText::FromString("Health"),
			                    FText::FromString("Recover 10% of your health"),
			                    nullptr,
			                    this);
			UpgradeItems.Add(TempHealth);

			UUpgradeButtonDataObject* TempGold = NewObject<UUpgradeButtonDataObject>(this);
			TempGold->SetData(FText::FromString("Gold"),
			                  FText::FromString("Gain 10 gold"),
			                  nullptr,
			                  this);
			UpgradeItems.Add(TempGold);
		}

		// Select up to three random options from the list of options
		for (int i = 0; i < 3 && UpgradeItems.Num() > 0; i++)
		{
			int Rand = FMath::RandRange(0, UpgradeItems.Num() - 1);
			UpgradesListView->AddItem(UpgradeItems[Rand]);
			UpgradeItems.RemoveAt(Rand);
		}
	}
	SetIsFocusable(true);
}

void ULevelUpWidget::ResumeButtonClicked()
{
	RemoveFromParent();

	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(PlayerController);
		PlayerController->bShowMouseCursor = false;
		PlayerController->SetPause(false);
	}

	SetIsFocusable(false);
}
