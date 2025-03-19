// Louis Hobbs | 2024-2025

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Pickupable.h"
#include "Pickup.generated.h"

class UPickupDataAsset;
class UTimelineComponent;
class USphereComponent;

UCLASS()
class VAMPIRES_API APickup : public AActor, public IPickupable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int PickupValue = 1;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USphereComponent* InnerSphereComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USphereComponent* OuterSphereComponent = nullptr;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMeshComponent = nullptr;

	UPROPERTY(EditDefaultsOnly)
	USoundBase* PickupSoundBase = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Timeline")
	TObjectPtr<UTimelineComponent> TimelineComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Timeline")
	UCurveFloat* CurveFloat;

private:
	FOnTimelineFloat onTimelineCallback;
	FOnTimelineEventStatic onTimelineFinishedCallback;

	FVector PickupLocation;

public:
	// Sets default values for this actor's properties
	APickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void LoadDataFromDataAsset_Implementation(UPickupDataAsset* PickupDataAsset) override;

	virtual void ResetData_Implementation() override;
	
	UFUNCTION()
	virtual void OnInnerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                                 const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnOuterBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                                 const FHitResult& SweepResult);

	UFUNCTION()
	void TimelineCallback(float val);

	UFUNCTION()
	void TimelineFinishedCallback();

	UFUNCTION(BlueprintCallable)
	void PlayTimeLine();
};
