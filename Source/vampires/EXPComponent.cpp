// Fill out your copyright notice in the Description page of Project Settings.


#include "EXPComponent.h"

// Sets default values for this component's properties
UEXPComponent::UEXPComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UEXPComponent::IncrementEXP(int value)
{
	int oldEXP = CurrentEXP;
	int oldLevel = CurrentLevel;
	
	CurrentEXP += value;
	OnEXPGained.Broadcast(CurrentEXP, GetCurrentLevelPercent());

	CurrentLevel = FMath::Floor(CurrentEXP / 100.0f);
	
	if (CurrentLevel != oldLevel)
	{
		OnEXPLevelUp.Broadcast(CurrentLevel);
	}
}

void UEXPComponent::SetCurrentEXP(int value)
{
	int oldEXP = CurrentEXP;
	int oldLevel = CurrentLevel;
	
	// TODO: I should be updating the level here
	CurrentEXP = value;
	OnEXPGained.Broadcast(CurrentEXP, GetCurrentLevelPercent());

	CurrentLevel = FMath::Floor(CurrentEXP / 100.0f);
	
	if (CurrentLevel != oldLevel)
	{
		OnEXPLevelUp.Broadcast(CurrentLevel);
	}
}

int UEXPComponent::GetCurrentEXP()
{
	return CurrentEXP;
}

int UEXPComponent::GetCurrentLevel()
{
	return CurrentLevel;
}

void UEXPComponent::Reset()
{
	CurrentEXP = 0;
	CurrentLevel = 0;
	OnEXPGained.Broadcast(CurrentEXP, GetCurrentLevelPercent());
	OnEXPLevelUp.Broadcast(CurrentLevel);
}

float UEXPComponent::GetCurrentLevelPercent()
{
	return (CurrentEXP % 100) / 100.0f;
}

// Called when the game starts
void UEXPComponent::BeginPlay()
{
	Super::BeginPlay();

	Reset();
}
