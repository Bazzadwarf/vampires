// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "EXPPickup.generated.h"

/**
 * 
 */
UCLASS()
class VAMPIRES_API AEXPPickup : public APickup
{
	GENERATED_BODY()

public:
	
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pickup")
	int EXP = 1;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaSeconds) override;

	virtual void OnInnerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                            const FHitResult& SweepResult) override;
};
