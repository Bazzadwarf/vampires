// Louis Hobbs | 2024-2025

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "VampireAIController.generated.h"

class AEnemyCharacter;
class APlayerCharacter;
class UBehaviorTreeComponent;
class UBlackboardComponent;
/**
 * 
 */
UCLASS()
class VAMPIRES_API AVampireAIController : public AAIController
{
	GENERATED_BODY()

	UPROPERTY()
	TObjectPtr<UBlackboardComponent> DefaultBlackboard;

	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> BehaviorTree;

	UPROPERTY()
	TObjectPtr<ACharacter> PlayerCharacter;

	UPROPERTY()
	TObjectPtr<AEnemyCharacter> EnemyCharacter;

	FTimerHandle PawnMoveToTimerHandle;

public:
	AVampireAIController(const FObjectInitializer& object_initializer);

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void OnPossess(APawn* InPawn) override;

	UFUNCTION()
	virtual void OnDamaged(FDamageInfo Info);

	UFUNCTION()
	virtual void OnDeath(FDamageInfo Info);

private:
	UFUNCTION()
	virtual void PawnMoveTo();
};
