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

		TArray<AWeapon*> Inventory = InventoryComponent->GetInventory();
		TArray<UUpgradeButtonDataObject*> upgradeItems;

		UpgradesListView->ClearListItems();

		for (AWeapon* weapon : Inventory)
		{
			if (weapon->CurrentLevel < weapon->Upgrades.Num())
			{
				UUpgradeButtonDataObject* Temp = NewObject<UUpgradeButtonDataObject>(this);
				Temp->SetData(weapon, this);
				upgradeItems.Add(Temp);
			}
		}

		TArray<TSubclassOf<AWeapon>> ObtainableWeapons = InventoryComponent->obtainableWeapons;

		for (TSubclassOf<AWeapon> weapon : ObtainableWeapons)
		{
			UUpgradeButtonDataObject* Temp = NewObject<UUpgradeButtonDataObject>(this);
			Temp->SetData(weapon, this);
			upgradeItems.Add(Temp);
		}
		
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

		UpgradesListView->SetListItems(upgradeItems);
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
