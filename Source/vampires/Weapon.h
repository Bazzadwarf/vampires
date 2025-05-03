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

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties")
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties")
	FText Description;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties")
	TObjectPtr<UTexture2D> Icon;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon Properties")
	TObjectPtr<USoundBase> WeaponActivatedSoundBase = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon Properties")
	TObjectPtr<UPaperSprite> WeaponSprite = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties")
	float WeaponCooldown = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties")
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties")
	TArray<FText> UpgradeDescriptions;
	
	int CurrentLevel = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properties")
	bool FollowPlayer = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int MaxLevel = 0;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UBoxComponent> BoxComponent = nullptr;

	TArray<TObjectPtr<AActor>> OverlappedEnemies = TArray<TObjectPtr<AActor>>();
	
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

	UFUNCTION()
	virtual void OnWeaponBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
							  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
							  const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnWeaponEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
							int32 OtherBodyIndex);

private:
	
	void ResizeBoxComponent(FViewport* Viewport, uint32 unused);
};
