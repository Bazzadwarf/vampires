// Louis Hobbs | 2024-2025


#include "GoldPickup.h"

#include "GoldComponent.h"

class APlayerCharacter;

void AGoldPickup::BeginPlay()
{
	Super::BeginPlay();
}

void AGoldPickup::OnInnerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                      UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                      const FHitResult& SweepResult)
{
	if (UGoldComponent* goldComponent = OtherActor->GetComponentByClass<UGoldComponent>())
	{
		goldComponent->IncrementGold(PickupValue);
		Super::OnInnerBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	}
}
