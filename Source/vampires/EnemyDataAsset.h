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
	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
	TObjectPtr<UStaticMesh> StaticMesh;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Pickups")
	TObjectPtr<UPickupDataAsset> CommonPickupDataAsset = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Pickups")
	TObjectPtr<UPickupDataAsset> UncommonPickupDataAsset = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Pickups")
	TObjectPtr<UPickupDataAsset> RarePickupDataAsset = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	TObjectPtr<USoundBase> OnDamagedSoundBase = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	TObjectPtr<USoundBase> OnDeathSoundBase = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Particles")
	TObjectPtr<UNiagaraSystem> OnDamagedNiagaraSystem;

	UPROPERTY(EditDefaultsOnly, Category = "Particles")
	TObjectPtr<UNiagaraSystem> OnDeathNiagaraSystem;

	UPROPERTY(EditDefaultsOnly, Category = "Properties")
	float MaxHealth = 100.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Properties")
	float MovementSpeed = 300.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Properties")
	float Damage = 5.0f;
};
