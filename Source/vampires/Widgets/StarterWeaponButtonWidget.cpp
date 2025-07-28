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
	if (UStarterWeaponButtonDataObject* Item = Cast<UStarterWeaponButtonDataObject>(ListItemObject))
	{
		WeaponNameTextBlock->SetText(Item->WeaponName);
		DescriptionTextBlock->SetText(Item->WeaponDescription);
		WeaponIcon->SetBrushFromTexture(Item->WeaponIcon);
		Parent = Item->Parent;
		WeaponTemplate = Item->WeaponTemplate;

		if (Body)
		{
			Body->OnClicked.AddUniqueDynamic(this, &UStarterWeaponButtonWidget::OnClicked);

			Body->OnHovered.AddUniqueDynamic(this, &UStarterWeaponButtonWidget::PlayHoveredSound);
			Body->OnHovered.AddUniqueDynamic(this, &UStarterWeaponButtonWidget::OnHoveredDelegate);

			Body->OnUnhovered.AddUniqueDynamic(this, &UStarterWeaponButtonWidget::OnUnhoveredDelegate);
			Body->OnUnhovered.AddUniqueDynamic(this, &UStarterWeaponButtonWidget::PlayUnhoveredSound);
		}
	}
}

void UStarterWeaponButtonWidget::OnClicked()
{
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
