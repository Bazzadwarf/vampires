// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UpgradeButtonDataObject.generated.h"

class AWeapon;
/**
 * 
 */
UCLASS(BlueprintType)
class VAMPIRES_API UUpgradeButtonDataObject : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText WeaponName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UTexture2D> WeaponIcon;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AWeapon> WeaponTemplate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<AWeapon> WeaponInstance;

	void SetData(AWeapon* Weapon);
	void SetData(TSubclassOf<AWeapon> Weapon);
};
