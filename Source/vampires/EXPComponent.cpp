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
	// TODO: I should be updating the level here
	CurrentEXP += value;
	OnEXPGained.ExecuteIfBound(value);
	OnEXPLevelUp.ExecuteIfBound(CurrentLevel);
}

void UEXPComponent::SetCurrentEXP(int value)
{
	// TODO: I should be updating the level here
	CurrentEXP = value;
	OnEXPGained.ExecuteIfBound(value);
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
	OnEXPGained.ExecuteIfBound(CurrentEXP);
	OnEXPLevelUp.ExecuteIfBound(CurrentLevel);
}

// Called when the game starts
void UEXPComponent::BeginPlay()
{
	Super::BeginPlay();

	Reset();
}
