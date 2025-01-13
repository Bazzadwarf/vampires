// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ProjectileDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class VAMPIRES_API UProjectileDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	float ProjectileSpeed = 500.0f;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMesh> StaticMesh;
};
