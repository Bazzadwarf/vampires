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
		BackButton->OnClicked.AddUniqueDynamic(this, &USelectWeaponWidget::PlayClickedSound);

		BackButton->OnHovered.AddUniqueDynamic(this, &USelectWeaponWidget::PlayHoveredSound);
		BackButton->OnHovered.AddUniqueDynamic(this, &USelectWeaponWidget::BackButtonTextBlockHoveredDelegate);

		BackButton->OnUnhovered.AddUniqueDynamic(this, &USelectWeaponWidget::BackButtonTextBlockUnhoveredDelegate);
		BackButton->OnUnhovered.AddUniqueDynamic(this, &USelectWeaponWidget::PlayUnhoveredSound);
	}

	if (UpgradesListView)
	{
		// Get a list of weapons that the player owns that can be upgraded
		for (TSubclassOf<AWeapon> Weapon : StarterWeapons)
		{
			UStarterWeaponButtonDataObject* Temp = NewObject<UStarterWeaponButtonDataObject>(this);
			Temp->SetData(Weapon, this);
			UpgradesListView->AddItem(Temp);
		}
	}
}

void USelectWeaponWidget::BackButtonClicked()
{
	if (PreviousWidget)
	{
		RemoveFromParent();

		UUserWidget* SelectWeaponWidget = CreateWidget<UUserWidget, APlayerController*>(
			UGameplayStatics::GetPlayerController(GetWorld(), 0), PreviousWidget);

		if (SelectWeaponWidget)
		{
			SelectWeaponWidget->AddToViewport();
		}
	}
}
