// Louis Hobbs | 2024-2025

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TableRows/ExpTableRow.h"
#include "EXPComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEXPGainedDelegate, int, exp, float, currentLevelPercent);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEXPLevelUpDelegate, int, level);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class VAMPIRES_API UEXPComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category="EXP")
	FOnEXPGainedDelegate OnEXPGained;

	UPROPERTY(BlueprintAssignable, Category="EXP")
	FOnEXPLevelUpDelegate OnEXPLevelUp;

	UPROPERTY(EditDefaultsOnly, Category="EXP")
	TObjectPtr<UDataTable> LevelsTable;

private:
	int CurrentEXP = 0;

	int CurrentLevel = 0;

	FExpTableRow NextLevelRow;

public:
	// Sets default values for this component's properties
	UEXPComponent();

	UFUNCTION(BlueprintCallable)
	void IncrementEXP(int Value);

	UFUNCTION(BlueprintCallable)
	void SetCurrentEXP(int Value);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetCurrentEXP();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int GetCurrentLevel();

	UFUNCTION(BlueprintCallable)
	void Reset();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetCurrentLevelPercent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
};
