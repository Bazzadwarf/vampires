// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Projectilable.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;
class USphereComponent;
class UProjectileDataAsset;

UCLASS()
class VAMPIRES_API AProjectile : public AActor, public IProjectilable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USphereComponent* SphereComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UProjectileMovementComponent* ProjectileMovement = nullptr;

	FVector TargetDirection = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ProjectileSpeed = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* StaticMeshComponent = nullptr;

	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void SetActorHiddenInGame(bool bNewHidden) override;

	virtual void SetTargetDirection_Implementation(FVector direction) override;

	virtual void LoadDataFromDataAsset_Implementation(UProjectileDataAsset* projectileDataAsset) override;

	virtual void ResetData_Implementation() override;

private:
	UFUNCTION()
	void OnProjectileBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                              UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                              const FHitResult& SweepResult);
};
