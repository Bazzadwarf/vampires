// Louis Hobbs | 2024-2025


#include "UpgradeButtonDataObject.h"

#include "vampires/Weapon.h"

void UUpgradeButtonDataObject::SetData(AWeapon* Weapon, UUserWidget* parent)
{
	WeaponName = Weapon->GetWeaponName();
	WeaponIcon = Weapon->GetIcon();
	WeaponInstance = Weapon;
	Parent = parent;
	
	if (Weapon->GetUpgradeDescriptions().Num() > Weapon->GetWeaponLevel())
	{
		Description = Weapon->GetUpgradeDescriptions()[Weapon->GetWeaponLevel()];
	}
}

void UUpgradeButtonDataObject::SetData(TSubclassOf<AWeapon> Weapon, UUserWidget* parent)
{
	if (AWeapon* tempWeapon = NewObject<AWeapon>(this, Weapon))
	{
		SetData(tempWeapon, parent);
	}
}

void UUpgradeButtonDataObject::SetData(FText weaponName, FText description, TObjectPtr<UTexture2D> weaponIcon,
                                       UUserWidget* parent)
{
	WeaponName = weaponName;
	Description = description;
	WeaponIcon = weaponIcon;
	Parent = parent;
}
