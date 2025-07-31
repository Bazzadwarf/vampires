// Louis Hobbs | 2024-2025


#include "UpgradeButtonDataObject.h"

#include "vampires/Weapon.h"

void UUpgradeButtonDataObject::SetData(AWeapon* Weapon, UUserWidget* ParentWidget)
{
	WeaponName = Weapon->GetWeaponName();
	WeaponIcon = Weapon->GetIcon();
	WeaponInstance = Weapon;
	Parent = ParentWidget;
	
	if (Weapon->GetUpgradeDescriptions().Num() > Weapon->GetWeaponLevel())
	{
		WeaponDescription = Weapon->GetUpgradeDescriptions()[Weapon->GetWeaponLevel()];
	}
}

void UUpgradeButtonDataObject::SetData(TSubclassOf<AWeapon> Weapon, UUserWidget* ParentWidget)
{
	if (AWeapon* tempWeapon = NewObject<AWeapon>(this, Weapon))
	{
		WeaponName = tempWeapon->GetWeaponName();
		WeaponDescription = tempWeapon->GetDescription();
		WeaponIcon = tempWeapon->GetIcon();
		WeaponTemplate = Weapon;
		Parent = ParentWidget;
	}
}

void UUpgradeButtonDataObject::SetData(FText NewWeaponName, FText NewDescription, TObjectPtr<UTexture2D> NewWeaponIcon,
                                       UUserWidget* ParentWidget)
{
	WeaponName = NewWeaponName;
	WeaponDescription = NewDescription;
	WeaponIcon = NewWeaponIcon;
	Parent = ParentWidget;
}
