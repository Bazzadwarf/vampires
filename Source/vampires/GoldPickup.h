// Louis Hobbs | 2024-2025

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "GoldPickup.generated.h"

/**
 * 
 */
UCLASS()
class VAMPIRES_API AGoldPickup : public APickup
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void OnInnerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                            const FHitResult& SweepResult) override;
};
