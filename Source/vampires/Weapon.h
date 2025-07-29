// Louis Hobbs | 2024-2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UnrealClient.h"
#include "Weapon.generated.h"

class UBoxComponent;
class UPaperSprite;
class UWeaponDataAsset;

UCLASS()
class VAMPIRES_API AWeapon : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon | Information")
	FText Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon | Information")
	FText Description;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon | Information")
	TObjectPtr<UTexture2D> Icon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon | Properties")
	TObjectPtr<USoundBase> WeaponActivatedSoundBase = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon | Properties")
	float WeaponCooldown = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon | Properties")
	float Damage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon | Properties")
	bool FollowPlayer = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon | Upgrades")
	TArray<FText> UpgradeDescriptions;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon | Upgrades")
	int MaxLevel = 0;

	UPROPERTY()
	TObjectPtr<UBoxComponent> BoxComponent = nullptr;

	TArray<TObjectPtr<AActor>> OverlappedEnemies = TArray<TObjectPtr<AActor>>();

	int CurrentLevel = 0;

private:
	FTimerHandle WeaponTimerHandle;

protected:
	// Sets default values for this actor's 
	AWeapon();

public:
	UFUNCTION(BlueprintNativeEvent)
	bool UpgradeWeapon();
	virtual bool UpgradeWeapon_Implementation();

	FText GetWeaponName() const { return Name; }

	FText GetDescription() const { return Description; }

	TObjectPtr<UTexture2D> GetIcon() const { return Icon; }

	float GetDamage() const { return Damage; }

	bool GetFollowPlayer() const { return FollowPlayer; }

	TArray<FText> GetUpgradeDescriptions() const { return UpgradeDescriptions; }

	int GetWeaponLevel() const { return CurrentLevel; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void ResetWeaponTimer();

	UFUNCTION(BlueprintNativeEvent)
	void FireWeaponAction();
	virtual void FireWeaponAction_Implementation();

	UFUNCTION()
	virtual void OnWeaponBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                                  const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnWeaponEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	                                UPrimitiveComponent* OtherComp,
	                                int32 OtherBodyIndex);

private:
	void ResizeBoxComponent(FViewport* Viewport, uint32 Unused);
};
