// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponInventoryComponent.h"
#include "Weapon.h"

// Sets default values for this component's properties
UWeaponInventoryComponent::UWeaponInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UWeaponInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	InitializeInventory();
}

void UWeaponInventoryComponent::InitializeInventory()
{
	inventory.Empty();

	for (TSubclassOf<AWeapon> weapon : initialInventory)
	{
		AddWeaponToInventory(weapon);
	}
}

void UWeaponInventoryComponent::AddWeaponToInventory(TSubclassOf<AWeapon> Weapon)
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = GetOwner();
	
	AWeapon* weapon = GetWorld()->SpawnActor<AWeapon>(Weapon, GetOwner()->GetTransform(), SpawnParameters);
	weapon->AttachToActor(GetOwner(), FAttachmentTransformRules::KeepRelativeTransform);
	inventory.Add(weapon);
}
