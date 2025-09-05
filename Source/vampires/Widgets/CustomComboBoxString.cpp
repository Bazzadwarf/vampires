// Louis Hobbs | 2024-2025


#include "CustomComboBoxString.h"

#include "Components/ComboBoxString.h"

void UCustomComboBoxString::NativeConstruct()
{
	Super::NativeConstruct();

	SetIsFocusable(true);

	ComboBox->OnSelectionChanged.AddDynamic(this, &UCustomComboBoxString::OnComboBoxSelectionChanged);
	ComboBox->OnOpening.AddDynamic(this, &UCustomComboBoxString::OnComboBoxOpening);

	SetDesiredFocusWidget(ComboBox);
}

void UCustomComboBoxString::NativeOnAddedToFocusPath(const FFocusEvent& InFocusEvent)
{
	Super::NativeOnAddedToFocusPath(InFocusEvent);
	OnFocused.Broadcast(InFocusEvent);
}

void UCustomComboBoxString::NativeOnRemovedFromFocusPath(const FFocusEvent& InFocusEvent)
{
	Super::NativeOnRemovedFromFocusPath(InFocusEvent);
	OnUnfocused.Broadcast(InFocusEvent);
}

void UCustomComboBoxString::OnComboBoxOpening()
{
	OnOpening.Broadcast();
}

void UCustomComboBoxString::OnComboBoxSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	OnSelectionChanged.Broadcast(SelectedItem, SelectionType);
}
