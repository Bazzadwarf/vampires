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
	Inventory.Empty();

	for (TSubclassOf<AWeapon> Weapon : InitialInventory)
	{
		if (IsValid(Weapon))
		{
			AddWeaponToInventory(Weapon);
		}
	}
}

void UWeaponInventoryComponent::AddWeaponToInventory(TSubclassOf<AWeapon> NewWeapon)
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = GetOwner();

	AWeapon* Weapon = GetWorld()->SpawnActor<AWeapon>(NewWeapon, SpawnParameters.Owner->GetTransform(), SpawnParameters);
	if (Weapon->GetFollowPlayer())
	{
		Weapon->AttachToActor(GetOwner(), FAttachmentTransformRules::KeepWorldTransform);
	}
	else
	{
		Weapon->SetActorLocation(FVector::ZeroVector);
	}

	Inventory.Add(Weapon);
	ObtainableWeapons.Remove(NewWeapon);
}

TArray<AWeapon*> UWeaponInventoryComponent::GetInventory()
{
	return Inventory;
}
