// Fill out your copyright notice in the Description page of Project Settings.


#include "VampireAIController.h"

#include "EnemyCharacter.h"
#include "HealthComponent.h"
#include "VampireCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Navigation/CrowdFollowingComponent.h"

AVampireAIController::AVampireAIController(const FObjectInitializer& object_initializer) : Super(
	object_initializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("Path Following Component")))
{
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard"));
	BehaviorTree = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Behavior Tree"));
}

void AVampireAIController::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(PawnMoveToTimerHandle, this, &AVampireAIController::PawnMoveTo, 0.25f, true);

	if (UCrowdFollowingComponent* CrowdFollowingComponent = FindComponentByClass<UCrowdFollowingComponent>())
	{
		CrowdFollowingComponent->SetCrowdSeparation(true);
		CrowdFollowingComponent->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Good);
		CrowdFollowingComponent->SetCrowdSeparationWeight(10.0f);
	}
}

void AVampireAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerCharacter)
	{
		Blackboard->SetValueAsVector("PlayerLocation", PlayerCharacter->GetActorLocation());
	}
}

void AVampireAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	EnemyCharacter = Cast<AEnemyCharacter>(InPawn);
	check(EnemyCharacter);
	EnemyCharacter->bUseControllerRotationYaw = false;
	EnemyCharacter->GetHealthComponent()->OnDamaged.AddDynamic(this, &AVampireAIController::OnDamaged);
	EnemyCharacter->GetHealthComponent()->OnDeath.AddDynamic(this, &AVampireAIController::OnDeath);

	PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	if (UBehaviorTree* bt = EnemyCharacter->GetBehaviorTree())
	{
		Blackboard->InitializeBlackboard(*bt->BlackboardAsset);
		BehaviorTree->StartTree(*bt);
		Blackboard->SetValueAsObject("SelfActor", EnemyCharacter);

		if (PlayerCharacter)
		{
			Blackboard->SetValueAsObject("Player", PlayerCharacter);
		}
	}
}

void AVampireAIController::OnDamaged(FDamageInfo info)
{
	if (EnemyCharacter->GetHealthComponent()->GetCurrentHealth() > 0.0f)
	{
		// TODO: Something
	}
}

void AVampireAIController::OnDeath(FDamageInfo info)
{
	// TODO: Do stuff here
	EnemyCharacter->OnDeath(info);
	/*EnemyCharacter->DetachFromControllerPendingDestroy();
	EnemyCharacter->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	EnemyCharacter->GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);

	if (UPawnMovementComponent* characterMovementComponent = EnemyCharacter->GetMovementComponent())
	{
		characterMovementComponent->StopMovementImmediately();
		characterMovementComponent->StopActiveMovement();
		characterMovementComponent->SetComponentTickEnabled(false);
	}
	GetWorldTimerManager().ClearTimer(PawnMoveToTimerHandle);
	EnemyCharacter->SetLifeSpan(0.1f);*/
}

void AVampireAIController::PawnMoveTo()
{
	MoveToActor(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0), 5);
}
