// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

class UPaperSprite;
class UWeaponDataAsset;

USTRUCT(BlueprintType)
struct FWeaponLevelUpgrades
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0.01f, ClampMax = 1.0f))
	float WeaponCooldownMultiplier = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0.01f))
	float WeaponDamageMultiplier = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0.01f))
	float WeaponRangeMultiplier = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText WeaponUpgradeText;
};

UCLASS()
class VAMPIRES_API AWeapon : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties")
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties")
	FText Description;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties")
	TObjectPtr<UTexture2D> Icon;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon Properties")
	USoundBase* WeaponActivatedSoundBase = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon Properties")
	TObjectPtr<UPaperSprite> WeaponSprite = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties")
	float WeaponCooldown = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties")
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties")
	TArray<FWeaponLevelUpgrades> Upgrades = TArray<FWeaponLevelUpgrades>();

private:
	FTimerHandle WeaponTimerHandle;

	int CurrentLevel = 0;

public:
	// Sets default values for this actor's properties
	AWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintNativeEvent)
	void FireWeaponAction();
	virtual void FireWeaponAction_Implementation();

	UFUNCTION()
	virtual bool UpgradeWeapon();
	virtual bool UpgradeWeapon(int newLevel);
};
