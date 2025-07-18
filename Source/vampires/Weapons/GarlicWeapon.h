// Louis Hobbs | 2024-2025

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

	UPROPERTY()
	TObjectPtr<AEnemyCharacter> OverlappedEnemyCharacter;

	FTimerHandle OverlappedTimerHandle;
};

/**
 * 
 */
UCLASS()
class VAMPIRES_API AGarlicWeapon : public AWeapon
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent> SphereComponent;

	TArray<FOverlappedEnemy> GarlicOverlappedEnemies;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> VisualEffectMeshComponent;

private:
	float Range;
public:
	AGarlicWeapon();

protected:
	virtual void BeginPlay() override;

public:
	virtual void FireWeaponAction_Implementation() override;

	UFUNCTION()
	void GarlicFireWeaponAction(FOverlappedEnemy EnemyCharacter);
	
	virtual bool UpgradeWeapon_Implementation() override;
	
protected:
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                    const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                  int32 OtherBodyIndex);
};
