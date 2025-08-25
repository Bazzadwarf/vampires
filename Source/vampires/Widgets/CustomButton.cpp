// Louis Hobbs | 2024-2025


#include "CustomButton.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UCustomButton::NativeConstruct()
{
	Super::NativeConstruct();

	SetIsFocusable(true);

	ButtonBody->OnClicked.AddUniqueDynamic(this, &UCustomButton::OnButtonClicked);
	ButtonBody->OnPressed.AddUniqueDynamic(this, &UCustomButton::OnButtonPressed);
	ButtonBody->OnReleased.AddUniqueDynamic(this, &UCustomButton::OnButtonReleased);
	ButtonBody->OnHovered.AddUniqueDynamic(this, &UCustomButton::OnButtonHovered);
	ButtonBody->OnUnhovered.AddUniqueDynamic(this, &UCustomButton::OnButtonUnhovered);

	TextBlock->SetText(ButtonText);
}

void UCustomButton::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	TextBlock->SetText(ButtonText);
}

TObjectPtr<UTextBlock> UCustomButton::GetTextBlock()
{
	return TextBlock;
}

void UCustomButton::OnButtonClicked()
{
	OnClicked.Broadcast();

	if (ButtonClickedSound)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), ButtonClickedSound);
	}
}

void UCustomButton::OnButtonPressed()
{
	OnPressed.Broadcast();

	if (ButtonPressedSound)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), ButtonPressedSound);
	}
}

void UCustomButton::OnButtonReleased()
{
	OnReleased.Broadcast();

	if (ButtonReleasedSound)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), ButtonReleasedSound);
	}
}

void UCustomButton::OnButtonHovered()
{
	OnHovered.Broadcast();

	if (ButtonHoveredSound)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), ButtonHoveredSound);
	}

	TextBlock->SetColorAndOpacity(FSlateColor(ButtonHoveredTextColor));
}

void UCustomButton::OnButtonUnhovered()
{
	OnUnhovered.Broadcast();
	
	if (ButtonUnhoveredSound)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), ButtonUnhoveredSound);
	}

	TextBlock->SetColorAndOpacity(FSlateColor(ButtonUnhoveredTextColor));
}
