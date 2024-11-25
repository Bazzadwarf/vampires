// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Weapon.h"
#include "GarlicWeapon.generated.h"

class USphereComponent;
class AEnemyCharacter;

USTRUCT()
struct FOverlappedEnemy
{
	GENERATED_BODY()

	AEnemyCharacter* OverlappedEnemyCharacter;

	FTimerHandle OverlappedTimerHandle;
};

/**
 * 
 */
UCLASS()
class VAMPIRES_API AGarlicWeapon : public AWeapon
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USphereComponent* SphereComponent;

	TArray<FOverlappedEnemy> OverlappedEnemies;

public:
	AGarlicWeapon();

protected:
	virtual void BeginPlay() override;

public:
	virtual void FireWeaponAction_Implementation() override;

	UFUNCTION()
	void GarlicFireWeaponAction(FOverlappedEnemy EnemyCharacter);

protected:
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                    const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                  int32 OtherBodyIndex);
};
