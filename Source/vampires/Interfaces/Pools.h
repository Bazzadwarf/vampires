// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Pools.generated.h"

class AObjectPoolManager;
// This class does not need to be modified.
UINTERFACE()
class UPools : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class VAMPIRES_API IPools
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent)
	AObjectPoolManager* GetEnemyObjectPoolManager();

	UFUNCTION(BlueprintNativeEvent)
	AObjectPoolManager* GetProjectileObjectPoolManager();
};
