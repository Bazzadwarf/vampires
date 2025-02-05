// Louis Hobbs | 2024-2025

#pragma once

#include "CoreMinimal.h"
#include "../Weapon.h"
#include "PentagramWeapon.generated.h"

class APickup;
class AEnemyCharacter;
class UBoxComponent;
/**
 * 
 */
UCLASS()
class VAMPIRES_API APentagramWeapon : public AWeapon
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UBoxComponent* BoxComponent = nullptr;

private:
	TArray<AEnemyCharacter*> OverlappedEnemies = TArray<AEnemyCharacter*>();

	TArray<APickup*> OverlappedPickups = TArray<APickup*>();

public:
	APentagramWeapon();

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
