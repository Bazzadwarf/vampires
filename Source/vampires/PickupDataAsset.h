// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PickupDataAsset.generated.h"

class UTimelineComponent;
class UPaperSprite;
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
	double PickupMovementRange = 500;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pickup Properties")
	double PickupMovementSpeed = 1000;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pickup Properties")
	TObjectPtr<UPaperSprite> WeaponSprite = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pickup Properties")
	TObjectPtr<USoundBase> PickupSoundBase = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pickup Properties")
	TObjectPtr<UCurveFloat> CurveFloat = nullptr;
};
