// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EXPComponent.generated.h"

DECLARE_DELEGATE(FOnEXPGainedDelegate)
DECLARE_DELEGATE(FOnEXPLevelUpDelegate)

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class VAMPIRES_API UEXPComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	FOnEXPGainedDelegate OnEXPGained;
	FOnEXPLevelUpDelegate OnEXPLevelUp;

protected:
	int CurrentEXP = 0;

	int CurrentLevel = 0;

public:
	// Sets default values for this component's properties
	UEXPComponent();

	UFUNCTION()
	void IncrementEXP(int value);

	UFUNCTION()
	void SetCurrentEXP(int value);

	UFUNCTION()
	int GetCurrentEXP();

	UFUNCTION()
	int GetCurrentLevel();

	UFUNCTION()
	void Reset();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
};
