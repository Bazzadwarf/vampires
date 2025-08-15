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
		BackButton->OnHovered.AddUniqueDynamic(this, &USelectWeaponWidget::BackButtonOnHovered);
		BackButton->OnUnhovered.AddUniqueDynamic(this, &USelectWeaponWidget::BackButtonOnUnhovered);
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
	PlayClickedSound();
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

void USelectWeaponWidget::BackButtonOnHovered()
{
	PlayHoveredSound();
	SetTextBlockHovered(BackTextBlock);
}

void USelectWeaponWidget::BackButtonOnUnhovered()
{
	PlayUnhoveredSound();
	SetTextBlockUnhovered(BackTextBlock);
}
