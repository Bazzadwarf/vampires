// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectileWeapon.h"
#include "FireWandWeapon.generated.h"

/**
 * 
 */
UCLASS()
class VAMPIRES_API AFireWandWeapon : public AProjectileWeapon
{
	GENERATED_BODY()

public:
	AFireWandWeapon();

protected:
	virtual void BeginPlay() override;

public:
	virtual void FireWeaponAction_Implementation() override;
};
