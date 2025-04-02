// Louis Hobbs | 2024-2025

#pragma once

#include "CoreMinimal.h"
#include "PickupDataAsset.h"
#include "VampireCharacter.h"
#include "Interfaces/Enemyable.h"
#include "EnemyCharacter.generated.h"

class USphereComponent;
class UObjectPoolComponent;
class UBehaviorTree;
class AEXPPickup;
/**
 * 
 */
UCLASS()
class VAMPIRES_API AEnemyCharacter : public AVampireCharacter, public IEnemyable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AEXPPickup> EXPPickupTemplate = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USphereComponent> DamageSphere = nullptr;

	UPROPERTY(EditDefaultsOnly)
	float Damage = 5.0f;;

	UPROPERTY(EditDefaultsOnly)
	float AttackCooldown = 1.0f;

private:
	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* BehaviorTree = nullptr;

	UObjectPoolComponent* ObjectPoolComponent = nullptr;

	UPickupDataAsset* PickupTemplate = nullptr;

	TArray<AActor*> Player;

	FTimerHandle DamageTimerHandle;

public:
	AEnemyCharacter(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UBehaviorTree* GetBehaviorTree();

	UFUNCTION()
	virtual void OnDamaged(FDamageInfo damageInfo);

	UFUNCTION()
	virtual void OnDeath(FDamageInfo damageInfo);
	
	UFUNCTION()
	virtual void LoadDataFromDataAsset_Implementation(UEnemyDataAsset* enemyDataAsset) override;

	UFUNCTION()
	virtual void ResetData_Implementation() override;

	UFUNCTION()
	virtual float GetCapsuleRadius_Implementation() override;

	UFUNCTION()
	virtual void SpawnController_Implementation() override;

	UFUNCTION()
	virtual UHealthComponent* GetEnemyHealthComponent_Implementation() override;

	UFUNCTION()
	void OnDamageBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
						UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
						const FHitResult& SweepResult);

	UFUNCTION()
	void OnDamageEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
					  int32 OtherBodyIndex);

private:
	UFUNCTION()
	void ResetHealth();

	void DamagePlayer();
};
