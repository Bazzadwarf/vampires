// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GoldComponent.generated.h"

DECLARE_DELEGATE(FOnGoldGainedDelegate)

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class VAMPIRES_API UGoldComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	FOnGoldGainedDelegate OnGoldGained;

protected:
	int CurrentGold = 0;

public:
	// Sets default values for this component's properties
	UGoldComponent();

	UFUNCTION()
	void IncrementGold(int value);

	UFUNCTION()
	void SetCurrentGold(int value);

	UFUNCTION()
	int GetCurrentGold();

	UFUNCTION()
	void Reset();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
};
