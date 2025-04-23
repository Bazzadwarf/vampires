// Louis Hobbs | 2024-2025


#include "ProjectileWeapon.h"

#include "../Weapon.h"

void AProjectileWeapon::FireWeaponAction_Implementation()
{
	Super::FireWeaponAction_Implementation();

	remainingProjectilesToSpawn = ProjectilesPerActivation;
	GetWorldTimerManager().SetTimer(FireProjectileTimerHandler, this, &AProjectileWeapon::FireProjectile, ProjectileSpawningDelay, true, 0.0f);
}

void AProjectileWeapon::FireProjectile()
{
	remainingProjectilesToSpawn--;
	if (remainingProjectilesToSpawn == 0)
	{
		GetWorldTimerManager().ClearTimer(FireProjectileTimerHandler);
	}
}
