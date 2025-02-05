// Fill out your copyright notice in the Description page of Project Settings.


#include "UpgradeButtonDataObject.h"

#include "vampires/Weapon.h"

void UUpgradeButtonDataObject::SetData(AWeapon* Weapon, UUserWidget* parent)
{
	WeaponName = Weapon->Name;
	Description = Weapon->Description;
	WeaponIcon = Weapon->Icon;
	WeaponInstance = Weapon;
	Parent = parent;
}

void UUpgradeButtonDataObject::SetData(TSubclassOf<AWeapon> Weapon, UUserWidget* parent)
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

void UUpgradeButtonDataObject::SetData(FText weaponName, FText description, TObjectPtr<UTexture2D> weaponIcon,
                                       UUserWidget* parent)
{
	WeaponName = weaponName;
	Description = description;
	WeaponIcon = weaponIcon;
	Parent = parent;
}
