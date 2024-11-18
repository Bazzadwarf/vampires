// Fill out your copyright notice in the Description page of Project Settings.


#include "GoldPickup.h"

#include "GoldComponent.h"

class APlayerCharacter;

void AGoldPickup::BeginPlay()
{
	Super::BeginPlay();
}

void AGoldPickup::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AGoldPickup::OnInnerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                      UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                      const FHitResult& SweepResult)
{
	if (UGoldComponent* goldComponent = OtherActor->GetComponentByClass<UGoldComponent>())
	{
		goldComponent->IncrementGold(Gold);
		Super::OnInnerBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	}
}
