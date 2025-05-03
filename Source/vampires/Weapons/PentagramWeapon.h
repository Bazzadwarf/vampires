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

private:
	TArray<TObjectPtr<APickup>> OverlappedPickups = TArray<TObjectPtr<APickup>>();

public:
	APentagramWeapon();
	
	virtual void FireWeaponAction_Implementation() override;

	bool UpgradeWeapon_Implementation() override;
	
	virtual void OnWeaponBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	
	virtual void OnWeaponEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
};
