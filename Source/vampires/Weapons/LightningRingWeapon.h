// Louis Hobbs | 2024-2025

#pragma once

#include "CoreMinimal.h"
#include "../Weapon.h"
#include "LightningRingWeapon.generated.h"

class AEnemyCharacter;
class USphereComponent;
/**
 * 
 */
UCLASS()
class VAMPIRES_API ALightningRingWeapon : public AWeapon
{
	GENERATED_BODY()

	USphereComponent* SphereComponent;

	TArray<AEnemyCharacter*> OverlappedEnemies;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int LightningBolts = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LightingBoltRadius = 200.0f;

public:
	ALightningRingWeapon();

protected:
	virtual void BeginPlay() override;

public:
	virtual void FireWeaponAction_Implementation() override;

	virtual bool UpgradeWeapon_Implementation() override;

protected:
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
						UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
						const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
					  int32 OtherBodyIndex);
};
