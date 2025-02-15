// Louis Hobbs | 2024-2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

class UPaperSprite;
class UWeaponDataAsset;

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
	TArray<FText> UpgradeDescriptions;
	
	int CurrentLevel = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int MaxLevel = 0;

private:
	FTimerHandle WeaponTimerHandle;


public:
	// Sets default values for this actor's properties
	AWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void ResetWeaponTimer();
	
public:
	UFUNCTION(BlueprintNativeEvent)
	void FireWeaponAction();
	virtual void FireWeaponAction_Implementation();

	UFUNCTION(BlueprintNativeEvent)
	bool UpgradeWeapon();
	virtual bool UpgradeWeapon_Implementation();
};
