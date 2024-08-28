// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "DetourCrowdAIController.h"
#include "EnemyCharacter.h"
#include "HealthComponent.h"
#include "PlayerCharacter.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "VampireAIController.generated.h"

/**
 * 
 */
UCLASS()
class VAMPIRES_API AVampireAIController : public AAIController
{
	GENERATED_BODY()

	UBlackboardComponent* Blackboard;

	UBehaviorTreeComponent* BehaviorTree;

	APlayerCharacter* PlayerCharacter;

	AEnemyCharacter* EnemyCharacter;

	FTimerHandle PawnMoveToTimerHandle;

public:
	AVampireAIController(const FObjectInitializer& object_initializer);

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void OnPossess(APawn* InPawn) override;

public:
	UFUNCTION()
	virtual void OnDamaged(FDamageInfo info);

	UFUNCTION()
	virtual void OnDeath(FDamageInfo info);

private:
	UFUNCTION()
	virtual void PawnMoveTo();
};
