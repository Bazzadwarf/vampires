// Louis Hobbs | 2024-2025

#pragma once

#include "CoreMinimal.h"
#include "../Weapon.h"
#include "LightningRingWeapon.generated.h"

class UNiagaraSystem;
class AEnemyCharacter;
class USphereComponent;
/**
 * 
 */
UCLASS()
class VAMPIRES_API ALightningRingWeapon : public AWeapon
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int LightningBolts = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LightingBoltRadius = 200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UNiagaraSystem> LightningEffectSystem;
	
public:
	ALightningRingWeapon();

protected:
	virtual void BeginPlay() override;

public:
	virtual void FireWeaponAction_Implementation() override;

	virtual bool UpgradeWeapon_Implementation() override;
};
