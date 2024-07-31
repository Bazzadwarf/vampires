// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectileWeapon.h"
#include "GunWeapon.generated.h"

/**
 * 
 */
UCLASS()
class VAMPIRES_API AGunWeapon : public AProjectileWeapon
{
	GENERATED_BODY()

public:
	AGunWeapon();

protected:
	virtual void BeginPlay() override;

public:
	virtual void FireWeaponAction_Implementation() override;
};
