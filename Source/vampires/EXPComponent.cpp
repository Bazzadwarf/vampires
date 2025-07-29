// Louis Hobbs | 2024-2025


#include "EXPComponent.h"

#include "TableRows/ExpTableRow.h"

// Sets default values for this component's properties
UEXPComponent::UEXPComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UEXPComponent::IncrementEXP(int Value)
{
	int OldLevel = CurrentLevel;
	CurrentEXP += Value;

	if (NextLevelRow.Level >= 0)
	{
		if (CurrentEXP >= NextLevelRow.CumulativeExpForNextLevel)
		{
			CurrentLevel = NextLevelRow.Level;

			if (FExpTableRow* NewRow = LevelsTable->FindRow<FExpTableRow>(
				FName(*FString::FromInt(NextLevelRow.Level + 1)), "", true))
			{
				NextLevelRow = *NewRow;
			}
			else
			{
				NextLevelRow.Level++;
				NextLevelRow.CumulativeExpForPreviousLevel = NextLevelRow.CumulativeExpForNextLevel;
				NextLevelRow.ExpRequiredForNextLevel += 16;
				NextLevelRow.CumulativeExpForNextLevel += NextLevelRow.ExpRequiredForNextLevel;
			}

			OnEXPLevelUp.Broadcast(CurrentLevel);
		}
	}
	else
	{
		CurrentLevel = FMath::Floor(CurrentEXP / 100.0f);

		if (CurrentLevel != OldLevel)
		{
			OnEXPLevelUp.Broadcast(CurrentLevel);
		}
	}

	OnEXPGained.Broadcast(CurrentEXP, GetCurrentLevelPercent());
}

void UEXPComponent::SetCurrentEXP(int Value)
{
	int OldLevel = CurrentLevel;
	CurrentEXP = Value;
	NextLevelRow = FExpTableRow();

	while (CurrentEXP < NextLevelRow.CumulativeExpForPreviousLevel && CurrentEXP < NextLevelRow.
		CumulativeExpForNextLevel)
	{
		if (FExpTableRow* NewRow = LevelsTable->FindRow<FExpTableRow>(FName(*FString::FromInt(NextLevelRow.Level + 1)),
		                                                              "", true))
		{
			NextLevelRow = *NewRow;
		}
		else
		{
			NextLevelRow.Level++;
			NextLevelRow.CumulativeExpForPreviousLevel = NextLevelRow.CumulativeExpForNextLevel;
			NextLevelRow.ExpRequiredForNextLevel += 16;
			NextLevelRow.CumulativeExpForNextLevel += NextLevelRow.ExpRequiredForNextLevel;
		}
	}

	OnEXPGained.Broadcast(CurrentEXP, GetCurrentLevelPercent());

	if (CurrentLevel != OldLevel)
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
	if (LevelsTable)
	{
		if (FExpTableRow* NewRow = LevelsTable->FindRow<FExpTableRow>(FName("1"), "", true))
		{
			NextLevelRow = *NewRow;
		}
	}

	CurrentEXP = 0;
	CurrentLevel = 0;
	OnEXPGained.Broadcast(CurrentEXP, GetCurrentLevelPercent());
	OnEXPLevelUp.Broadcast(CurrentLevel);
}

float UEXPComponent::GetCurrentLevelPercent()
{
	int AdjustedCurrentExp = CurrentEXP - NextLevelRow.CumulativeExpForPreviousLevel;
	float CurrentLevelPercent = static_cast<float>(AdjustedCurrentExp) / static_cast<float>(NextLevelRow.
		ExpRequiredForNextLevel);

	if (FMath::IsNaN(CurrentLevelPercent))
	{
		return 0.0f;
	}

	return CurrentLevelPercent;
}

// Called when the game starts
void UEXPComponent::BeginPlay()
{
	Super::BeginPlay();

	Reset();
}
