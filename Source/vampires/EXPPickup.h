// Louis Hobbs | 2024-2025

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

protected:
	virtual void BeginPlay() override;

	virtual void OnInnerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                                 const FHitResult& SweepResult) override;
};
