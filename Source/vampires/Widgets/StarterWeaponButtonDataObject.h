﻿// Louis Hobbs | 2024-2025

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "StarterWeaponButtonDataObject.generated.h"

class AWeapon;
/**
 * 
 */
UCLASS()
class VAMPIRES_API UStarterWeaponButtonDataObject : public UObject
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UUserWidget> Parent;

	void SetData(AWeapon* Weapon, UUserWidget* parent);
	void SetData(TSubclassOf<AWeapon> Weapon, UUserWidget* parent);
	void SetData(FText weaponName, FText description, TObjectPtr<UTexture2D> weaponIcon, UUserWidget* parent);
};
