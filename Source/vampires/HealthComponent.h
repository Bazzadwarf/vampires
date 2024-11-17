// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

USTRUCT()
struct FDamageInfo
{
	GENERATED_BODY()

	UPROPERTY()
	AActor* DamagedActor;

	UPROPERTY()
	float Damage;

	UPROPERTY()
	const UDamageType* DamageType;

	UPROPERTY()
	AController* InstigatedBy;

	UPROPERTY()
	AActor* DamageCauser;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDamageDelegate, FDamageInfo, damageInfo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDeathDelegate, FDamageInfo, damageInfo);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class VAMPIRES_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	FOnDamageDelegate OnDamaged;
	FOnDeathDelegate OnDeath;

protected:
	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 100.f;

	UPROPERTY(VisibleAnywhere)
	float CurrentHealth;

	bool IsDead = false;

	bool CanDamage = true;

public:
	// Sets default values for this component's properties
	UHealthComponent();

	UFUNCTION()
	virtual void TakeDamage(AActor* damagedActor, float damage, const UDamageType* damageType,
	                        AController* instigatedBy,
	                        AActor* damageCauser);

	UFUNCTION()
	void IncrementHealth(float value);

	UFUNCTION()
	float GetMaxHealth();

	UFUNCTION()
	void SetMaxHealth(float value);

	UFUNCTION()
	float GetCurrentHealth();

	UFUNCTION()
	void SetCurrentHealth(float value);

	UFUNCTION()
	void ResetHealth();

	UFUNCTION()
	void RecoverHealth(float healing);

	UFUNCTION()
	bool GetIsDead();

	UFUNCTION()
	void SetIsDead(bool isDead);

	UFUNCTION()
	bool GetCanDamage();

	UFUNCTION()
	void SetCanDamage(bool canDamage);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
};
