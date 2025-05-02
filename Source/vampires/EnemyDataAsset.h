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
	UStaticMesh* StaticMesh;

	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* BehaviorTree = nullptr;

	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess = "true"))
	UPickupDataAsset* PickupDataAsset = nullptr;
	
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USoundBase> OnDamagedSoundBase = nullptr;

	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USoundBase> OnDeathSoundBase = nullptr;

	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess = "true"))
	UNiagaraSystem* OnDamagedNiagaraSystem;

	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess = "true"))
	UNiagaraSystem* OnDeathNiagaraSystem;
};
