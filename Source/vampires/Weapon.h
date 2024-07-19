// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class VAMPIRES_API AWeapon : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY()
	float WeaponCooldown = 1.0f;

	UPROPERTY()
	float Damage;

private:
	FTimerHandle WeaponTimerHandle;

public:
	// Sets default values for this actor's properties
	AWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	virtual void FireWeaponAction();

	UFUNCTION()
	virtual void UpgradeWeapon(int newLevel);
};
