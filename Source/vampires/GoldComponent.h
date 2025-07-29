// Louis Hobbs | 2024-2025

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GoldComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGoldGainedDelegate, int, gold);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class VAMPIRES_API UGoldComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	FOnGoldGainedDelegate OnGoldGained;

private:
	int CurrentGold = 0;

public:
	// Sets default values for this component's properties
	UGoldComponent();

	UFUNCTION()
	void IncrementGold(int Value);

	UFUNCTION()
	void SetCurrentGold(int Value);

	UFUNCTION()
	int GetCurrentGold();

	UFUNCTION()
	void Reset();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
};
