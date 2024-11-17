// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HealthComponent.h"
#include "GameFramework/GameMode.h"
#include "VampireGameMode.generated.h"

class AObjectPoolManager;
class AVampirePlayerController;
class APlayerCharacter;
class AEnemyCharacter;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemyDeathCountIncrementDelegate, int, level);

UCLASS()
class VAMPIRES_API AVampireGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AEnemyCharacter> EnemyTemplate;

	FOnEnemyDeathCountIncrementDelegate OnEnemyDeathCountIncrementDelegate;

private:
	TObjectPtr<APlayerCharacter> PlayerCharacter;

	TObjectPtr<AVampirePlayerController> PlayerController;

	FTimerHandle SpawnEnemyTimerDelegate;

	int EnemyDeathCount = 0;

	TObjectPtr<AObjectPoolManager> EnemyObjectPoolManager = nullptr;

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetEnemyDeathCount();

	UFUNCTION()
	void HandleOnEnemyDeath(FDamageInfo damageInfo);
	
	UFUNCTION()
	void IncrementEnemyDeathCount();

	AObjectPoolManager* GetEnemyObjectPoolManager();

protected:
	UFUNCTION()
	void SpawnEnemy();
};
