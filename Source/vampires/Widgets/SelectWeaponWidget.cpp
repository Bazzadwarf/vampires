// Louis Hobbs | 2024-2025


#include "SelectWeaponWidget.h"

#include "MainMenuWidget.h"
#include "StarterWeaponButtonDataObject.h"
#include "UpgradeButtonDataObject.h"
#include "Components/Button.h"
#include "Components/ListView.h"
#include "Kismet/GameplayStatics.h"

void USelectWeaponWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (BackButton)
	{
		BackButton->OnClicked.AddUniqueDynamic(this, &USelectWeaponWidget::BackButtonClicked);
	}

	if (UpgradesListView)
	{
		// Get a list of weapons that the player owns that can be upgraded
		for (TSubclassOf<AWeapon> weapon : starterWeapons)
		{
			UStarterWeaponButtonDataObject* Temp = NewObject<UStarterWeaponButtonDataObject>(this);
			Temp->SetData(weapon, this);
			UpgradesListView->AddItem(Temp);
		}
	}
}

void USelectWeaponWidget::BackButtonClicked()
{
	if (PreviousWidget)
	{
		RemoveFromParent();

		UUserWidget* selectWeaponWidget = CreateWidget<UUserWidget, APlayerController*>(
			UGameplayStatics::GetPlayerController(GetWorld(), 0), PreviousWidget);

		if (selectWeaponWidget)
		{
			selectWeaponWidget->AddToViewport();
		}
	}	
}
