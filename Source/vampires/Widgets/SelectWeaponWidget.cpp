// Louis Hobbs | 2024-2025


#include "SelectWeaponWidget.h"

#include "CustomButton.h"
#include "StarterWeaponButtonDataObject.h"
#include "StarterWeaponButtonWidget.h"
#include "Components/ScrollBox.h"
#include "Kismet/GameplayStatics.h"

void USelectWeaponWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (BackButton)
	{
		BackButton->OnClicked.AddUniqueDynamic(this, &USelectWeaponWidget::BackButtonClicked);
		BackButton->OnFocused.AddUniqueDynamic(this, &USelectWeaponWidget::BackButtonFocused);
	}

	if (StarterWeaponsScrollBox && StarterWeaponButtonWidgetTemplate)
	{
		for (TSubclassOf<AWeapon> Weapon : StarterWeapons)
		{
			if (UStarterWeaponButtonWidget* Widget = CreateWidget<UStarterWeaponButtonWidget>(
				GetWorld(), StarterWeaponButtonWidgetTemplate))
			{
				UStarterWeaponButtonDataObject* Temp = NewObject<UStarterWeaponButtonDataObject>(this);
				Temp->SetData(Weapon, this);
				Widget->SetData(Temp);
				StarterWeaponsScrollBox->AddChild(Widget);
				Buttons.Push(Widget);
			}
		}

		if (Buttons.Num() > 0)
		{
			Buttons[0]->SetKeyboardFocus();
		}
	}
}

FReply USelectWeaponWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	CurrentFocus->SetKeyboardFocus();

	return Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);
}

void USelectWeaponWidget::BackButtonClicked()
{
	if (PreviousWidget)
	{
		RemoveFromParent();

		UUserWidget* MainMenuWidget = CreateWidget<UUserWidget, APlayerController*>(
			UGameplayStatics::GetPlayerController(GetWorld(), 0), PreviousWidget);

		if (MainMenuWidget)
		{
			MainMenuWidget->AddToViewport();
		}
	}
}

void USelectWeaponWidget::BackButtonFocused(FFocusEvent InFocusEvent)
{
	SetCurrentFocus(BackButton);
}
