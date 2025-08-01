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
	FOnEnemyDeathCountIncrementDelegate OnEnemyDeathCountIncrementDelegate;

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AEnemyCharacter> EnemyTemplate;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AProjectile> ProjectileTemplate;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AEXPPickup> PickupTemplate;

	UPROPERTY(EditDefaultsOnly)
	TArray<TObjectPtr<UEnemyDataAsset>> EnemyDataAssets;

private:
	UPROPERTY()
	TObjectPtr<APlayerCharacter> PlayerCharacter;

	UPROPERTY()
	TObjectPtr<AVampirePlayerController> PlayerController;

	FTimerHandle SpawnEnemyTimerDelegate;

	int EnemyDeathCount = 0;

	UPROPERTY()
	TObjectPtr<AObjectPoolManager> EnemyObjectPoolManager = nullptr;

	UPROPERTY()
	TObjectPtr<AObjectPoolManager> ProjectileObjectPoolManager = nullptr;

	UPROPERTY()
	TObjectPtr<AObjectPoolManager> PickupObjectPoolManager = nullptr;

	UPROPERTY()
	TArray<TObjectPtr<UEnemyDataAsset>> SpawnableEnemyDataAssets;

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetEnemyDeathCount();

protected:
	UFUNCTION()
	void HandleOnEnemyDeath(FDamageInfo DamageInfo);

	UFUNCTION()
	void IncrementEnemyDeathCount();

	virtual AObjectPoolManager* GetEnemyObjectPoolManager_Implementation() override;

	virtual AObjectPoolManager* GetProjectileObjectPoolManager_Implementation() override;

	virtual AObjectPoolManager* GetPickupObjectPoolManager_Implementation() override;

	UFUNCTION(BlueprintCallable)
	void AddRandomEnemyTypeToPool();

	UFUNCTION()
	void OnPlayerDeath(FDamageInfo DamageInfo);
	
	UFUNCTION(BlueprintCallable)
	void EndGame();

	UFUNCTION()
	void SpawnEnemy();
};
