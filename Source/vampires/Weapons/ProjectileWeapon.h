// Louis Hobbs | 2024-2025

#pragma once

#include "CoreMinimal.h"
#include "vampires/Weapon.h"
#include "ProjectileWeapon.generated.h"

class UProjectileDataAsset;
class AProjectile;

/**
 * 
 */
UCLASS()
class VAMPIRES_API AProjectileWeapon : public AWeapon
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Weapon | Projectiles")
	TObjectPtr<UProjectileDataAsset> ProjectileTemplate = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon | Projectiles")
	int ProjectilesPerActivation = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon | Projectiles")
	float ProjectileSpawningDelay = 0.25f;

protected:
	FTimerHandle FireProjectileTimerHandler;

private:
	int remainingProjectilesToSpawn = 0;

public:
	virtual void FireWeaponAction_Implementation() override;

protected:
	UFUNCTION()
	virtual void FireProjectile();
};
