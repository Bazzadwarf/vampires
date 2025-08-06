// Louis Hobbs | 2024-2025


#include "OptionsMenuWidget.h"

#include <string>

#include "Components/Button.h"
#include "Components/ComboBoxString.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"


void UOptionsMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GenerateResolutionOptions();

	if (ReturnButton)
	{
		ReturnButton->OnClicked.AddUniqueDynamic(this, &UOptionsMenuWidget::ReturnButtonOnClicked);
		ReturnButton->OnClicked.AddUniqueDynamic(this, &UOptionsMenuWidget::PlayClickedSound);

		ReturnButton->OnHovered.AddUniqueDynamic(this, &UOptionsMenuWidget::PlayHoveredSound);
		ReturnButton->OnHovered.AddUniqueDynamic(this, &UOptionsMenuWidget::ReturnTextBlockHoveredDelegate);

		ReturnButton->OnUnhovered.AddUniqueDynamic(this, &UOptionsMenuWidget::ReturnTextBlockUnhoveredDelegate);
		ReturnButton->OnUnhovered.AddUniqueDynamic(this, &UOptionsMenuWidget::PlayUnhoveredSound);
	}
}

void UOptionsMenuWidget::GenerateResolutionOptions()
{
	ResolutionComboBox->ClearOptions();

	TArray<FIntPoint> Resolutions;
	UKismetSystemLibrary::GetSupportedFullscreenResolutions(Resolutions);
	for (FIntPoint Resolution : Resolutions)
	{
		ResolutionComboBox->AddOption(FString::FromInt(Resolution.X) + "x" + FString::FromInt(Resolution.Y));
	}

	FVector2D Resolution = FVector2D::ZeroVector;
	GEngine->GameViewport->GetViewportSize(Resolution);
	FString ResolutionString = FString::FromInt(Resolution.X) + "x" + FString::FromInt(Resolution.Y);
	if (ResolutionComboBox->FindOptionIndex(ResolutionString) == -1)
	{
		ResolutionComboBox->AddOption(ResolutionString);
	}

	ResolutionComboBox->SetSelectedOption(ResolutionString);
}

void UOptionsMenuWidget::ReturnButtonOnClicked()
{
	if (MainMenuMenuWidget)
	{
		RemoveFromParent();

		UUserWidget* SelectWeaponWidget = CreateWidget<UUserWidget, APlayerController*>(
			UGameplayStatics::GetPlayerController(GetWorld(), 0), MainMenuMenuWidget);

		if (SelectWeaponWidget)
		{
			SelectWeaponWidget->AddToViewport();
		}
	}
}
