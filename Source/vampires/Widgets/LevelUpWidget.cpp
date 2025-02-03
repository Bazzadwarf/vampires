// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelUpWidget.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Button.h"
#include "Components/ListView.h"
#include "Kismet/GameplayStatics.h"
#include "UpgradeButtonDataObject.h"
#include "EntitySystem/MovieSceneEntitySystemRunner.h"
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
		ACharacter* Player = Cast<AVampireCharacter>( UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (!Player) return;

		UWeaponInventoryComponent* InventoryComponent = Player->GetComponentByClass<UWeaponInventoryComponent>();
		if (!InventoryComponent) return;

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
