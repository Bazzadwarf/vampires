// Louis Hobbs | 2024-2025

#pragma once

#include "CoreMinimal.h"
#include "ProjectileWeapon.h"
#include "MagicWandWeapon.generated.h"

/**
 * 
 */
UCLASS()
class VAMPIRES_API AMagicWandWeapon : public AProjectileWeapon
{
	GENERATED_BODY()

public:
	AMagicWandWeapon();

protected:
	virtual void BeginPlay() override;

public:
	virtual void FireWeaponAction_Implementation() override;

	virtual bool UpgradeWeapon_Implementation() override;

	protected:
	virtual void FireProjectile() override;
};
