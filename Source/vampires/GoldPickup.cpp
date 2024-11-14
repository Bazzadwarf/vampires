// Fill out your copyright notice in the Description page of Project Settings.


#include "GoldPickup.h"

#include "GoldComponent.h"
#include "PlayerCharacter.h"

class APlayerCharacter;

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
	if (APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor))
	{
		PlayerCharacter->GetGoldComponent()->IncrementGold(Gold);
		Super::OnBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	}
}
