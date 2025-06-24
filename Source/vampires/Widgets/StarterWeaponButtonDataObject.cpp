// Louis Hobbs | 2024-2025


#include "StarterWeaponButtonDataObject.h"

#include "vampires/Weapon.h"

void UStarterWeaponButtonDataObject::SetData(AWeapon* Weapon, UUserWidget* parent)
{
	WeaponName = Weapon->Name;
	Description = Weapon->UpgradeDescriptions[Weapon->CurrentLevel];
	WeaponIcon = Weapon->Icon;
	WeaponInstance = Weapon;
	Parent = parent;
}

void UStarterWeaponButtonDataObject::SetData(TSubclassOf<AWeapon> Weapon, UUserWidget* parent)
{
	AWeapon* temp = NewObject<AWeapon>(this, Weapon);
	if (temp)
	{
		WeaponName = temp->Name;
		Description = temp->Description;
		WeaponIcon = temp->Icon;
		WeaponTemplate = Weapon;
		Parent = parent;
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
