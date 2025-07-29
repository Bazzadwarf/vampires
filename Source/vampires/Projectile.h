// Louis Hobbs | 2024-2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Projectilable.h"
#include "Projectile.generated.h"

class UNiagaraComponent;
class UProjectileMovementComponent;
class USphereComponent;
class UProjectileDataAsset;

UCLASS()
class VAMPIRES_API AProjectile : public AActor, public IProjectilable
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USphereComponent> SphereComponent = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UNiagaraComponent> NiagaraRibbonComponent = nullptr;

	UPROPERTY(EditDefaultsOnly)
	float ProjectileSpeed = 500.0f;

	UPROPERTY(EditDefaultsOnly)
	int RemainingDamageableEnemies = 1;

	UPROPERTY(EditDefaultsOnly)
	float ProjectileLifespan = 15.0f;

	FTimerHandle ProjectileLifetimeTimerHandle;

	FVector TargetDirection = FVector::ZeroVector;

	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void SetActorHiddenInGame(bool bNewHidden) override;

	virtual void SetTargetDirection_Implementation(FVector Direction) override;

	virtual void LoadDataFromDataAsset_Implementation(UProjectileDataAsset* ProjectileDataAsset) override;

	virtual void ResetData_Implementation() override;

private:
	UFUNCTION()
	void OnProjectileBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                              UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                              const FHitResult& SweepResult);

	UFUNCTION()
	void ReturnProjectileToPool();
};
