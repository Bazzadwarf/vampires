// Louis Hobbs | 2024-2025


#include "StarterWeaponButtonWidget.h"

#include "StarterWeaponButtonDataObject.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "vampires/VampireGameInstance.h"

void UStarterWeaponButtonWidget::SetData(UStarterWeaponButtonDataObject* ListItemObject)
{
	if (UStarterWeaponButtonDataObject* Item = Cast<UStarterWeaponButtonDataObject>(ListItemObject))
	{
		TextBlock->SetText(Item->WeaponName);
		ButtonText = Item->WeaponName;
		DescriptionTextBlock->SetText(Item->WeaponDescription);
		WeaponIcon->SetBrushFromTexture(Item->WeaponIcon);
		Parent = Item->Parent;
		WeaponTemplate = Item->WeaponTemplate;
	}
}

void UStarterWeaponButtonWidget::OnButtonClicked()
{
	Super::OnButtonClicked();

	if (UVampireGameInstance* GameInstance = Cast<UVampireGameInstance>(GetGameInstance()))
	{
		GameInstance->StarterWeapon = WeaponTemplate;

		if (!GameInstance->GameWorld.IsNull())
		{
			UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), GameInstance->GameWorld);

			if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
			{
				PlayerController->bShowMouseCursor = false;
				UWidgetBlueprintLibrary::SetInputMode_GameOnly(PlayerController);
			}
			SetIsFocusable(false);
		}
	}
}
