// Louis Hobbs | 2024-2025


#include "StarterWeaponButtonWidget.h"

#include "StarterWeaponButtonDataObject.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "vampires/VampireGameInstance.h"

void UStarterWeaponButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UStarterWeaponButtonWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UStarterWeaponButtonDataObject* Item = Cast<UStarterWeaponButtonDataObject>(ListItemObject);
	
	if (Item)
	{
		WeaponNameTextBlock->SetText(Item->WeaponName);
		DescriptionTextBlock->SetText(Item->Description);
		WeaponIcon->SetBrushFromTexture(Item->WeaponIcon);
		Parent = Item->Parent;
		WeaponTemplate = Item->WeaponTemplate;

		if (Body)
		{
			Body->OnClicked.AddUniqueDynamic(this, &UStarterWeaponButtonWidget::OnClicked);
		}
	}
}

void UStarterWeaponButtonWidget::OnClicked()
{
	if (UVampireGameInstance* gameInstance = Cast<UVampireGameInstance>(GetGameInstance()))
	{
		gameInstance->StarterWeapon = WeaponTemplate;

		if (!gameInstance->GameWorld.IsNull())
		{
			UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), gameInstance->GameWorld);

			if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
			{
				PlayerController->bShowMouseCursor = false;
				UWidgetBlueprintLibrary::SetInputMode_GameOnly(PlayerController);
			}
			SetIsFocusable(false);
		}
	}
}
