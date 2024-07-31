// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectileWeapon.h"
#include "MagicWandWeapon.generated.h"

/**
 * 
 */
UCLASS()
class VAMPIRES_API AMagicWandWeapon : public AProjectileWeapon
{
	GENERATED_BODY()

public:
	AMagicWandWeapon();

protected:
	virtual void BeginPlay() override;

public:
	virtual void FireWeaponAction_Implementation() override;
};
