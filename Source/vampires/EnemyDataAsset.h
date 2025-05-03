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
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TObjectPtr<UStaticMesh> StaticMesh;

	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBehaviorTree> BehaviorTree = nullptr;

	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPickupDataAsset> PickupDataAsset = nullptr;
	
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USoundBase> OnDamagedSoundBase = nullptr;

	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USoundBase> OnDeathSoundBase = nullptr;

	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UNiagaraSystem> OnDamagedNiagaraSystem;

	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UNiagaraSystem> OnDeathNiagaraSystem;
};
