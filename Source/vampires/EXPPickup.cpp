// Fill out your copyright notice in the Description page of Project Settings.


#include "EXPPickup.h"

void AEXPPickup::BeginPlay()
{
	Super::BeginPlay();
}

void AEXPPickup::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AEXPPickup::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// TODO: Add EXP to player EXP component
	
	Super::OnBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}
