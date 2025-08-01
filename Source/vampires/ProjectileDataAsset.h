// Louis Hobbs | 2024-2025

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ProjectileDataAsset.generated.h"

class UNiagaraSystem;
/**
 * 
 */
UCLASS()
class VAMPIRES_API UProjectileDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	float ProjectileSpeed = 1000.0f;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMesh> StaticMesh;

	UPROPERTY(EditAnywhere)
	int DamageableEnemies = 1;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UNiagaraSystem> NiagaraRibbonSystem = nullptr;
};
