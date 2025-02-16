// Louis Hobbs | 2024-2025

#pragma once

#include "CoreMinimal.h"
#include "HealthComponent.h"
#include "GameFramework/GameMode.h"
#include "Interfaces/Pools.h"
#include "VampireGameMode.generated.h"

class AEXPPickup;
class UEnemyDataAsset;
class AProjectile;
class AObjectPoolManager;
class AVampirePlayerController;
class APlayerCharacter;
class AEnemyCharacter;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemyDeathCountIncrementDelegate, int, level);

UCLASS()
class VAMPIRES_API AVampireGameMode : public AGameMode, public IPools
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AEnemyCharacter> EnemyTemplate;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AProjectile> ProjectileTemplate;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AEXPPickup> PickupTemplate;

	FOnEnemyDeathCountIncrementDelegate OnEnemyDeathCountIncrementDelegate;

	UPROPERTY(EditDefaultsOnly)
	TArray<TObjectPtr<UEnemyDataAsset>> EnemyDataAssets;

private:
	TObjectPtr<APlayerCharacter> PlayerCharacter;

	TObjectPtr<AVampirePlayerController> PlayerController;

	FTimerHandle SpawnEnemyTimerDelegate;

	int EnemyDeathCount = 0;

	TObjectPtr<AObjectPoolManager> EnemyObjectPoolManager = nullptr;

	TObjectPtr<AObjectPoolManager> ProjectileObjectPoolManager = nullptr;

	TObjectPtr<AObjectPoolManager> PickupObjectPoolManager = nullptr;

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetEnemyDeathCount();

	UFUNCTION()
	void HandleOnEnemyDeath(FDamageInfo damageInfo);

	UFUNCTION()
	void IncrementEnemyDeathCount();

	virtual AObjectPoolManager* GetEnemyObjectPoolManager_Implementation() override;

	virtual AObjectPoolManager* GetProjectileObjectPoolManager_Implementation() override;

	virtual AObjectPoolManager* GetPickupObjectPoolManager_Implementation() override;

protected:
	UFUNCTION()
	void SpawnEnemy();
};
