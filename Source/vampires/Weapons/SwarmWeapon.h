// Louis Hobbs | 2024-2025

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "vampires/Weapon.h"
#include "SwarmWeapon.generated.h"

UCLASS()
class VAMPIRES_API ASwarmWeapon : public AWeapon
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Timeline")
	TObjectPtr<UTimelineComponent> TimelineComponent = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UCurveFloat> SwarmCurve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TimelinePlayRate = 1;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class AActor> SwarmActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Distance = 250.0f;


	
private:
	FOnTimelineFloat onTimelineCallback;

	TArray<AActor*> SwarmActors;
	
public:
	// Sets default values for this actor's properties
	ASwarmWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION()
	void TimelineCallback(float val);
	
	virtual bool UpgradeWeapon_Implementation() override;	
};
