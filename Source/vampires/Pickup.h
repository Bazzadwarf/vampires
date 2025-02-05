// Louis Hobbs | 2024-2025

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

class UPickupDataAsset;
class UTimelineComponent;
class USphereComponent;
class UPaperSpriteComponent;

UCLASS()
class VAMPIRES_API APickup : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UPickupDataAsset> PickupDataAsset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	double PickupMovementRange = 500;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	double PickupMovementSpeed = 1000;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USphereComponent* InnerSphereComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USphereComponent* OuterSphereComponent = nullptr;

	UPROPERTY(EditAnywhere)
	UPaperSpriteComponent* SpriteComponent = nullptr;

	UPROPERTY(EditDefaultsOnly)
	USoundBase* PickupSoundBase = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Timeline")
	TObjectPtr<UTimelineComponent> TimelineComponent;

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
