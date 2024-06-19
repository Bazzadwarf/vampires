// Fill out your copyright notice in the Description page of Project Settings.


#include "GoldComponent.h"

// Sets default values for this component's properties
UGoldComponent::UGoldComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UGoldComponent::IncrementGold(int value)
{
	CurrentGold += value;
	OnGoldGained.ExecuteIfBound();
}

void UGoldComponent::SetCurrentGold(int value)
{
	CurrentGold = value;
	OnGoldGained.ExecuteIfBound();
}

int UGoldComponent::GetCurrentGold()
{
	return CurrentGold;
}

void UGoldComponent::Reset()
{
	CurrentGold = 0;
}

// Called when the game starts
void UGoldComponent::BeginPlay()
{
	Super::BeginPlay();

	Reset();
}
