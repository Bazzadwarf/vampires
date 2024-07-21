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
	GetWorldTimerManager().SetTimer(WeaponTimerHandle, this, &AWeapon::FireWeaponAction, WeaponCooldown, true);
	UEXPComponent* expcomponent = GetOwner()->GetComponentByClass<UEXPComponent>();

	if (expcomponent)
	{
		expcomponent->OnEXPLevelUp.BindUObject(this, &AWeapon::UpgradeWeapon);
	}
}

void AWeapon::FireWeaponAction_Implementation()
{
	// Do stuff
}

void AWeapon::UpgradeWeapon(int newLevel)
{
}
