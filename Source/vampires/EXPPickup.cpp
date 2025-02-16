// Louis Hobbs | 2024-2025


#include "EXPPickup.h"
#include "EXPComponent.h"

void AEXPPickup::BeginPlay()
{
	Super::BeginPlay();
}

void AEXPPickup::OnInnerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                     UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                     const FHitResult& SweepResult)
{
	if (UEXPComponent* expComponent = OtherActor->GetComponentByClass<UEXPComponent>())
	{
		expComponent->IncrementEXP(PickupValue);
		Super::OnInnerBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	}
}
