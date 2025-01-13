// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Projectilable.generated.h"

class UProjectileDataAsset;
// This class does not need to be modified.
UINTERFACE()
class UProjectilable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class VAMPIRES_API IProjectilable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent)
	void LoadDataFromDataAsset(UProjectileDataAsset* projectileDataAsset);

	UFUNCTION(BlueprintNativeEvent)
	void ResetData();

	UFUNCTION(BlueprintNativeEvent)
	void SetTargetDirection(FVector direction);
};
