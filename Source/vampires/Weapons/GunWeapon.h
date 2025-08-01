// Louis Hobbs | 2024-2025

#pragma once

#include "CoreMinimal.h"
#include "ProjectileWeapon.h"
#include "GunWeapon.generated.h"

/**
 * 
 */
UCLASS()
class VAMPIRES_API AGunWeapon : public AProjectileWeapon
{
	GENERATED_BODY()

public:
	AGunWeapon();

protected:
	virtual void BeginPlay() override;

public:
	virtual void FireWeaponAction_Implementation() override;

	virtual bool UpgradeWeapon_Implementation() override;

protected:
	virtual void FireProjectile() override;

private:
	void SpawnProjectile(AActor* Projectile, const FVector& Direction);
};
