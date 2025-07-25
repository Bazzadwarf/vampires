// Louis Hobbs | 2024-2025


#include "StarterWeaponButtonDataObject.h"

#include "vampires/Weapon.h"

void UStarterWeaponButtonDataObject::SetData(AWeapon* Weapon, UUserWidget* parent)
{
	WeaponName = Weapon->GetWeaponName();
	Description = Weapon->GetDescription();
	WeaponIcon = Weapon->GetIcon();
	WeaponInstance = Weapon;
	Parent = parent;
}

void UStarterWeaponButtonDataObject::SetData(TSubclassOf<AWeapon> Weapon, UUserWidget* parent)
{
	if (AWeapon* tempWeapon = NewObject<AWeapon>(this, Weapon))
	{
		SetData(tempWeapon, parent);
		WeaponTemplate = Weapon;
	}
}

void UStarterWeaponButtonDataObject::SetData(FText weaponName, FText description, TObjectPtr<UTexture2D> weaponIcon,
	UUserWidget* parent)
{
	WeaponName = weaponName;
	Description = description;
	WeaponIcon = weaponIcon;
	Parent = parent;
}
