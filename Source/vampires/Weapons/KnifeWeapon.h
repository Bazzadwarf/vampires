// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectileWeapon.h"
#include "KnifeWeapon.generated.h"

/**
 * 
 */
UCLASS()
class VAMPIRES_API AKnifeWeapon : public AProjectileWeapon
{
	GENERATED_BODY()

public:
	AKnifeWeapon();

protected:
	virtual void BeginPlay() override;

public:
	virtual void FireWeaponAction_Implementation() override;
};
