// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Enemyable.generated.h"

class UHealthComponent;
class UEnemyDataAsset;

// This class does not need to be modified.
UINTERFACE()
class UEnemyable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class VAMPIRES_API IEnemyable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent)
	void LoadDataFromDataAsset(UEnemyDataAsset* projectileDataAsset);

	UFUNCTION(BlueprintNativeEvent)
	void ResetData();

	UFUNCTION(BlueprintNativeEvent)
	float GetCapsuleRadius();

	UFUNCTION(BlueprintNativeEvent)
	void SpawnController();

	UFUNCTION(BlueprintNativeEvent)
	UHealthComponent* GetEnemyHealthComponent();
};
