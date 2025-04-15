// Louis Hobbs | 2024-2025

#pragma once

#include "CoreMinimal.h"
#include "vampires/Weapon.h"
#include "ProjectileWeapon.generated.h"

class UProjectileDataAsset;
class AProjectile;
class UBoxComponent;

/**
 * 
 */
UCLASS()
class VAMPIRES_API AProjectileWeapon : public AWeapon
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UBoxComponent* BoxComponent = nullptr;

	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
	TObjectPtr<UProjectileDataAsset> ProjectileTemplate = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int ProjectilesPerActivation = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float ProjectileSpawningDelay = 0.25f;

protected:
	TArray<AActor*> OverlappedEnemies = TArray<AActor*>();

	FTimerHandle FireProjectileTimerHandler;

private:
	int remainingProjectilesToSpawn = 0;

public:
	AProjectileWeapon();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION()
	void OnWeaponBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                          UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                          const FHitResult& SweepResult);

	UFUNCTION()
	void OnWeaponEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                        int32 OtherBodyIndex);

	virtual void FireWeaponAction_Implementation() override;

protected:
	UFUNCTION()
	virtual void FireProjectile();
};
