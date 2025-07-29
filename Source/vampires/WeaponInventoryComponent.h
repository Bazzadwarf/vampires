// Louis Hobbs | 2024-2025

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponInventoryComponent.generated.h"


class AWeapon;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class VAMPIRES_API UWeaponInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<AWeapon>> ObtainableWeapons;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<AWeapon>> InitialInventory;

private:
	UPROPERTY()
	TArray<TObjectPtr<AWeapon>> Inventory;

public:
	// Sets default values for this component's properties
	UWeaponInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UFUNCTION()
	void InitializeInventory();

	UFUNCTION()
	void AddWeaponToInventory(TSubclassOf<AWeapon> NewWeapon);

	UFUNCTION()
	TArray<AWeapon*> GetInventory();
};
