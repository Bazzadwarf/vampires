// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Weapon.h"
#include "Components/SphereComponent.h"
#include "vampires/EnemyCharacter.h"
#include "GarlicWeapon.generated.h"

/**
 * 
 */
UCLASS()
class VAMPIRES_API AGarlicWeapon : public AWeapon
{
	GENERATED_BODY()

	USphereComponent* SphereComponent;

	TArray<AEnemyCharacter*> OverlappedEnemies;

public:
	AGarlicWeapon();

protected:
	virtual void BeginPlay() override;

public:
	virtual void FireWeaponAction_Implementation() override;

protected:
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                    const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                  int32 OtherBodyIndex);
};
