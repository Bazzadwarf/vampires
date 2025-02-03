// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

#include "EXPComponent.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	TArray<AWeapon*> example;
	GetWorldTimerManager().SetTimer(WeaponTimerHandle, this, &AWeapon::FireWeaponAction, WeaponCooldown, true);
	UEXPComponent* expcomponent = GetOwner()->GetComponentByClass<UEXPComponent>();

	if (expcomponent)
	{
		expcomponent->OnEXPLevelUp.AddUniqueDynamic(this, &AWeapon::UpgradeWeapon);
	}
}

void AWeapon::FireWeaponAction_Implementation()
{
	// Do stuff
}

bool AWeapon::UpgradeWeapon()
{
	return UpgradeWeapon(CurrentLevel + 1);
}

bool AWeapon::UpgradeWeapon(int newLevel)
{
	if (newLevel < Upgrades.Num())
	{
		WeaponCooldown *= Upgrades[newLevel].WeaponCooldownMultiplier;
		Damage *= Upgrades[newLevel].WeaponDamageMultiplier;
		
		GetWorldTimerManager().ClearTimer(WeaponTimerHandle);
		GetWorldTimerManager().SetTimer(WeaponTimerHandle, this, &AWeapon::FireWeaponAction, WeaponCooldown, true);
		return true;
	}
	
	return false;
}
