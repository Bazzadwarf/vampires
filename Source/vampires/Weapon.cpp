// Louis Hobbs | 2024-2025


#include "Weapon.h"

#include "EXPComponent.h"
#include "Kismet/GameplayStatics.h"

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
}

void AWeapon::ResetWeaponTimer()
{
	GetWorldTimerManager().ClearTimer(WeaponTimerHandle);
	GetWorldTimerManager().SetTimer(WeaponTimerHandle, this, &AWeapon::FireWeaponAction, WeaponCooldown, true);
}

void AWeapon::FireWeaponAction_Implementation()
{
	// This should be overridden in child weapon classes

	if (WeaponActivatedSoundBase)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), WeaponActivatedSoundBase);
	}
}

bool AWeapon::UpgradeWeapon_Implementation()
{
	if (CurrentLevel < MaxLevel)
	{
		CurrentLevel++;
		return true;
	}
	
	return false;
}
