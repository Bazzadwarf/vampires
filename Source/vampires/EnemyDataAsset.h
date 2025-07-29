// Louis Hobbs | 2024-2025

#pragma once

#include "CoreMinimal.h"
#include "PickupDataAsset.h"
#include "Engine/DataAsset.h"
#include "EnemyDataAsset.generated.h"

class UBehaviorTree;
class UNiagaraSystem;

/**
 * 
 */
UCLASS()
class VAMPIRES_API UEnemyDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMesh> StaticMesh;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UBehaviorTree> BehaviorTree = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UPickupDataAsset> PickupDataAsset = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USoundBase> OnDamagedSoundBase = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USoundBase> OnDeathSoundBase = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UNiagaraSystem> OnDamagedNiagaraSystem;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UNiagaraSystem> OnDeathNiagaraSystem;
};
