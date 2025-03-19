// Louis Hobbs | 2024-2025

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PickupDataAsset.generated.h"

class UTimelineComponent;
/**
 * 
 */
UCLASS(BlueprintType)
class VAMPIRES_API UPickupDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pickup Properties")
	int PickupValue = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pickup Properties")
	TObjectPtr<UStaticMesh> PickupStaticMesh = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pickup Properties")
	TObjectPtr<USoundBase> PickupSoundBase = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pickup Properties")
	TObjectPtr<UCurveFloat> CurveFloat = nullptr;
};
