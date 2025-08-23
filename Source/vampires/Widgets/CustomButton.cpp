// Louis Hobbs | 2024-2025


#include "CustomButton.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"

void UCustomButton::NativeConstruct()
{
	Super::NativeConstruct();

	ButtonBody->OnClicked.AddUniqueDynamic(this, &UCustomButton::OnButtonClicked);
	ButtonBody->OnPressed.AddUniqueDynamic(this, &UCustomButton::OnButtonPressed);
	ButtonBody->OnReleased.AddUniqueDynamic(this, &UCustomButton::OnButtonReleased);
	ButtonBody->OnHovered.AddUniqueDynamic(this, &UCustomButton::OnButtonHovered);
	ButtonBody->OnUnhovered.AddUniqueDynamic(this, &UCustomButton::OnButtonHovered);

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
}

void UCustomButton::OnButtonPressed()
{
	OnPressed.Broadcast();
}

void UCustomButton::OnButtonReleased()
{
	OnReleased.Broadcast();
}

void UCustomButton::OnButtonHovered()
{
	OnHovered.Broadcast();
}
