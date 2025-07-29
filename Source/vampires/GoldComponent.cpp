// Louis Hobbs | 2024-2025


#include "GoldComponent.h"

// Sets default values for this component's properties
UGoldComponent::UGoldComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UGoldComponent::IncrementGold(int Value)
{
	CurrentGold += Value;
	OnGoldGained.Broadcast(CurrentGold);
}

void UGoldComponent::SetCurrentGold(int Value)
{
	CurrentGold = Value;
	OnGoldGained.Broadcast(CurrentGold);
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
