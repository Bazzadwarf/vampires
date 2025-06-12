// Louis Hobbs | 2024-2025


#include "SelectWeaponWidget.h"

#include "MainMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void USelectWeaponWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (BackButton)
	{
		BackButton->OnClicked.AddUniqueDynamic(this, &USelectWeaponWidget::BackButtonClicked);
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
