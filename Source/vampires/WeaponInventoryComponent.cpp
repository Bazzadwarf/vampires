// Louis Hobbs | 2024-2025


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
		if (IsValid(weapon))
		{
			AddWeaponToInventory(weapon);
		}
	}
}

void UWeaponInventoryComponent::AddWeaponToInventory(TSubclassOf<AWeapon> Weapon)
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = GetOwner();
	
	AWeapon* weapon = GetWorld()->SpawnActor<AWeapon>(Weapon, SpawnParameters.Owner->GetTransform(), SpawnParameters);
	if (weapon->GetFollowPlayer())
	{
		weapon->AttachToActor(GetOwner(), FAttachmentTransformRules::KeepWorldTransform);
	}
	else
	{
		weapon->SetActorLocation(FVector::ZeroVector);
	}
	
	inventory.Add(weapon);
	obtainableWeapons.Remove(Weapon);
}

TArray<AWeapon*> UWeaponInventoryComponent::GetInventory()
{
	return inventory;
}
