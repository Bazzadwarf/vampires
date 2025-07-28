// Louis Hobbs | 2024-2025


#include "StarterWeaponButtonDataObject.h"

#include "vampires/Weapon.h"

void UStarterWeaponButtonDataObject::SetData(AWeapon* Weapon, UUserWidget* ParentWidget)
{
	WeaponName = Weapon->GetWeaponName();
	WeaponDescription = Weapon->GetDescription();
	WeaponIcon = Weapon->GetIcon();
	WeaponInstance = Weapon;
	Parent = ParentWidget;
}

void UStarterWeaponButtonDataObject::SetData(TSubclassOf<AWeapon> Weapon, UUserWidget* ParentWidget)
{
	if (AWeapon* tempWeapon = NewObject<AWeapon>(this, Weapon))
	{
		SetData(tempWeapon, ParentWidget);
		WeaponTemplate = Weapon;
	}
}

void UStarterWeaponButtonDataObject::SetData(FText NewWeaponName, FText NewWeaponDescription, TObjectPtr<UTexture2D> NewWeaponIcon,
	UUserWidget* ParentWidget)
{
	WeaponName = NewWeaponName;
	WeaponDescription = NewWeaponDescription;
	WeaponIcon = NewWeaponIcon;
	Parent = ParentWidget;
}
