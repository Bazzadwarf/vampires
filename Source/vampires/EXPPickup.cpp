// Fill out your copyright notice in the Description page of Project Settings.


#include "EXPPickup.h"
#include "EXPComponent.h"

void AEXPPickup::BeginPlay()
{
	Super::BeginPlay();
}

void AEXPPickup::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AEXPPickup::OnInnerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                     UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                     const FHitResult& SweepResult)
{
	if (UEXPComponent* expComponent = OtherActor->GetComponentByClass<UEXPComponent>())
	{
		expComponent->IncrementEXP(EXP);
		Super::OnInnerBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	}
}
