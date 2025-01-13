// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WeaponDataAsset.generated.h"

class UPaperSprite;
class AProjectile;

USTRUCT(BlueprintType)
struct FWeaponLevelUpgrades
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WeaponCooldownMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WeaponDamageMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WeaponRangeMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText WeaponUpgradeText;
};

/**
 * 
 */
UCLASS(BlueprintType)
class VAMPIRES_API UWeaponDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Weapon Properties")
	TSubclassOf<AProjectile> ProjectileTemplate = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon Properties")
	USoundBase* WeaponActivatedSoundBase = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon Properties")
	TObjectPtr<UPaperSprite> WeaponSprite = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon Upgrades")
	TArray<FWeaponLevelUpgrades> WeaponLevelUpgrades = TArray<FWeaponLevelUpgrades>();
};
