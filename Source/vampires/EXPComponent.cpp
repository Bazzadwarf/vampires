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

void UEXPComponent::IncrementEXP(int value)
{
	int oldEXP = CurrentEXP;
	int oldLevel = CurrentLevel;
	
	CurrentEXP += value;
	
	if (NextLevelRow.Level >= 0)
	{
		if (CurrentEXP >= NextLevelRow.CumulativeExpForNextLevel)
		{
			CurrentLevel = NextLevelRow.Level;
	
			if (FExpTableRow* newRow = LevelsTable->FindRow<FExpTableRow>(FName(*FString::FromInt(NextLevelRow.Level + 1)),"", true))
			{
				NextLevelRow = *newRow;	
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
		
		if (CurrentLevel != oldLevel)
		{
			OnEXPLevelUp.Broadcast(CurrentLevel);
		}
	}
	
	OnEXPGained.Broadcast(CurrentEXP, GetCurrentLevelPercent());
}

void UEXPComponent::SetCurrentEXP(int value)
{
	int oldEXP = CurrentEXP;
	int oldLevel = CurrentLevel;
	
	CurrentEXP = value;
	
	NextLevelRow = FExpTableRow();
	
	while (CurrentEXP < NextLevelRow.CumulativeExpForPreviousLevel && CurrentEXP < NextLevelRow.CumulativeExpForNextLevel)
	{
		if (FExpTableRow* newRow = LevelsTable->FindRow<FExpTableRow>(FName(*FString::FromInt(NextLevelRow.Level + 1)),"", true))
		{
			NextLevelRow = *newRow;	
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
	if (LevelsTable)
	{
		if (FExpTableRow* newRow = LevelsTable->FindRow<FExpTableRow>(FName("1"), "", true))
		{
			NextLevelRow = *newRow;
		}
	}
	
	CurrentEXP = 0;
	CurrentLevel = 0;
	OnEXPGained.Broadcast(CurrentEXP, GetCurrentLevelPercent());
	OnEXPLevelUp.Broadcast(CurrentLevel);
}

float UEXPComponent::GetCurrentLevelPercent()
{
	int adjustedCurrentExp = CurrentEXP - NextLevelRow.CumulativeExpForPreviousLevel;
	float res = static_cast<float>(adjustedCurrentExp) / static_cast<float>(NextLevelRow.ExpRequiredForNextLevel);

	if (FMath::IsNaN(res))
	{
		return 0.0f;
	}

	return res;
}

// Called when the game starts
void UEXPComponent::BeginPlay()
{
	Super::BeginPlay();

	Reset();
}
