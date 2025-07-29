// Louis Hobbs | 2024-2025

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Pickupable.h"
#include "Pickup.generated.h"

class UNiagaraComponent;
class UPickupDataAsset;
class UTimelineComponent;
class USphereComponent;

UCLASS()
class VAMPIRES_API APickup : public AActor, public IPickupable
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int PickupValue = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<USphereComponent> InnerSphereComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<USphereComponent> OuterSphereComponent = nullptr;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USoundBase> PickupSoundBase = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Timeline")
	TObjectPtr<UTimelineComponent> TimelineComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Timeline")
	TObjectPtr<UCurveFloat> CurveFloat;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UNiagaraComponent> NiagaraComponent = nullptr;

private:
	FOnTimelineFloat OnTimelineCallback;
	FOnTimelineEventStatic OnTimelineFinishedCallback;

	FVector PickupLocation;

public:
	// Sets default values for this actor's properties
	APickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void LoadDataFromDataAsset_Implementation(UPickupDataAsset* PickupDataAsset, FVector Location) override;

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
	void TimelineCallback(float Value);

	UFUNCTION()
	void TimelineFinishedCallback();

	UFUNCTION(BlueprintCallable)
	void PlayTimeLine();
};
