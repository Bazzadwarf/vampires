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
	TArray<TSubclassOf<AWeapon>> initialInventory;

private:
	UPROPERTY()
	TArray<AWeapon*> inventory;

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
	void AddWeaponToInventory(TSubclassOf<AWeapon> Weapon);

	UFUNCTION()
	TArray<AWeapon*> GetInventory();
};
