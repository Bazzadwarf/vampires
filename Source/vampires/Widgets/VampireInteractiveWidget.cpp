// Louis Hobbs | 2024-2025


#include "VampireInteractiveWidget.h"

#include "Components/TextBlock.h"
#include "GameFramework/GameUserSettings.h"
#include "Kismet/GameplayStatics.h"

void UVampireInteractiveWidget::SetReturnScreen(UUserWidget* UserWidget)
{
	if (UserWidget)
	{
		PreviousScreen = UserWidget;
	}
}

void UVampireInteractiveWidget::PlayHoveredSound()
{
	if (ButtonHoveredSound)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), ButtonHoveredSound);
	}
}

void UVampireInteractiveWidget::SetTextBlockHovered(UTextBlock* TextBlock)
{
	TextBlock->SetColorAndOpacity(FSlateColor(ButtonHoveredTextColor));
}

void UVampireInteractiveWidget::SetTextBlockUnhovered(UTextBlock* TextBlock)
{
	TextBlock->SetColorAndOpacity(FSlateColor(ButtonUnhoveredTextColor));
}

void UVampireInteractiveWidget::PlayUnhoveredSound()
{
	if (ButtonUnhoveredSound)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), ButtonUnhoveredSound);
	}
}

void UVampireInteractiveWidget::PlayClickedSound()
{
	if (ButtonClickedSound)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), ButtonClickedSound);
	}
}

void UVampireInteractiveWidget::ReturnToPreviousScreen()
{
	GEngine->GameUserSettings->ApplySettings(false);

	this->RemoveFromParent();
	PreviousScreen->AddToViewport();
}
