// Louis Hobbs | 2024-2025


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
		TArray<UUpgradeButtonDataObject*> upgradeItems;
		for (AWeapon* weapon : Inventory)
		{
			if (weapon->GetWeaponLevel() < weapon->GetUpgradeDescriptions().Num())
			{
				UUpgradeButtonDataObject* Temp = NewObject<UUpgradeButtonDataObject>(this);
				Temp->SetData(weapon, this);
				upgradeItems.Add(Temp);
			}
		}

		// Get list of weapons that the player can still obtain 
		TArray<TSubclassOf<AWeapon>> ObtainableWeapons = InventoryComponent->obtainableWeapons;
		for (TSubclassOf<AWeapon> weapon : ObtainableWeapons)
		{
			UUpgradeButtonDataObject* Temp = NewObject<UUpgradeButtonDataObject>(this);
			Temp->SetData(weapon, this);
			upgradeItems.Add(Temp);
		}

		// If no valid options exist, populate list with default options
		if (upgradeItems.Num() == 0)
		{
			UUpgradeButtonDataObject* tempHealth = NewObject<UUpgradeButtonDataObject>(this);
			tempHealth->SetData(FText::FromString("Health"),
					  FText::FromString("Recover 10% of your health"),
					  nullptr,
					     this);
			upgradeItems.Add(tempHealth);

			UUpgradeButtonDataObject* tempGold = NewObject<UUpgradeButtonDataObject>(this);
			tempGold->SetData(FText::FromString("Gold"),
					FText::FromString("Gain 10 gold"),
					nullptr,
					   this);
			upgradeItems.Add(tempGold);
		}

		// Select up to three random options from the list of options
		for (int i = 0; i < 3 && upgradeItems.Num() > 0; i++)
		{
			int rand = FMath::RandRange(0, upgradeItems.Num() - 1);
			UpgradesListView->AddItem(upgradeItems[rand]);
			upgradeItems.RemoveAt(rand);
		}
	}
	SetIsFocusable(true);
}

void ULevelUpWidget::ResumeButtonClicked()
{
	RemoveFromParent();

	if (APlayerController* playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(playerController);
		playerController->bShowMouseCursor = false;
		playerController->SetPause(false);
	}

	SetIsFocusable(false);
}
