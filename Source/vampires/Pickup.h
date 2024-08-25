// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "PaperSpriteComponent.h"
#include "Pickup.generated.h"

UCLASS()
class VAMPIRES_API APickup : public AActor
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	double PickupMovementRange = 500;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	double PickupMovementSpeed = 1000;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USphereComponent* SphereComponent = nullptr;
		
	UPROPERTY(EditAnywhere)
	UPaperSpriteComponent* SpriteComponent = nullptr;

	UPROPERTY(EditDefaultsOnly)
	USoundBase* PickupSoundBase = nullptr;
	
public:	
	// Sets default values for this actor's properties
	APickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                            const FHitResult& SweepResult);
};
