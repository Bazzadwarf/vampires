// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EXPPickup.h"
#include "VampireCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "EnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class VAMPIRES_API AEnemyCharacter : public AVampireCharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AEXPPickup> EXPPickupTemplate = nullptr;
	
private:

	UPROPERTY(EditDefaultsOnly, Meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* BehaviorTree = nullptr;
	
public:
	AEnemyCharacter(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UBehaviorTree* GetBehaviorTree();

	UFUNCTION()
	virtual void OnDamaged();

	UFUNCTION()
	virtual void OnDeath();
};
