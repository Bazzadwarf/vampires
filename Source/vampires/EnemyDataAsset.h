// Louis Hobbs | 2024-2025

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EnemyDataAsset.generated.h"

class UPaperFlipbook;
class UBehaviorTree;

/**
 * 
 */
UCLASS()
class VAMPIRES_API UEnemyDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UPaperFlipbook* PaperFlipbook;

	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* BehaviorTree = nullptr;
};
