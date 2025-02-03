// Fill out your copyright notice in the Description page of Project Settings.


#include "UpgradeButtonDataObject.h"

#include "vampires/Weapon.h"

void UUpgradeButtonDataObject::SetData(AWeapon* Weapon)
{
	WeaponName = Weapon->Name;
	Description = Weapon->Description;
	WeaponIcon = Weapon->Icon;
	WeaponInstance = Weapon;
}

void UUpgradeButtonDataObject::SetData(TSubclassOf<AWeapon> Weapon)
{
	AWeapon* temp = NewObject<AWeapon>(this, Weapon);
	if (temp)
	{
		WeaponName = temp->Name;
		Description = temp->Description;
		WeaponIcon = temp->Icon;
		WeaponTemplate = Weapon;
	}
}
