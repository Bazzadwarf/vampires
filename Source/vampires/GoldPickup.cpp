// Fill out your copyright notice in the Description page of Project Settings.


#include "GoldPickup.h"

void AGoldPickup::BeginPlay()
{
	Super::BeginPlay();
}

void AGoldPickup::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AGoldPickup::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// TODO: Add Gold to player Gold component
	
	Super::OnBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}
