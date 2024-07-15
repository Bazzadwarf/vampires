// Fill out your copyright notice in the Description page of Project Settings.


#include "VampireAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"

AVampireAIController::AVampireAIController(const FObjectInitializer& object_initializer)
{
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard"));
	BehaviorTree = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Behavior Tree"));
}

void AVampireAIController::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(PawnMoveToTimerHandle, this, &AVampireAIController::PawnMoveTo, 0.25f, true);
}

void AVampireAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (AVampireCharacter* Player = Cast<AVampireCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		Blackboard->SetValueAsObject("Player", Player);
		auto location = Player->GetActorLocation();
		Blackboard->SetValueAsVector("PlayerLocation", location);
	}
}

void AVampireAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	EnemyCharacter = Cast<AEnemyCharacter>(InPawn);
	check(EnemyCharacter);
	EnemyCharacter->GetHealthComponent()->OnDamaged.BindUFunction(this, "OnDamaged");
	EnemyCharacter->GetHealthComponent()->OnDeath.BindUFunction(this, "OnDeath");

	if (UBehaviorTree* bt = EnemyCharacter->GetBehaviorTree())
	{
		Blackboard->InitializeBlackboard(*bt->BlackboardAsset);
		BehaviorTree->StartTree(*bt);
		Blackboard->SetValueAsObject("SelfActor", EnemyCharacter);
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
	EnemyCharacter->DetachFromControllerPendingDestroy();
	EnemyCharacter->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	EnemyCharacter->GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);

	if (UPawnMovementComponent* characterMovementComponent = EnemyCharacter->GetMovementComponent())
	{
		characterMovementComponent->StopMovementImmediately();
		characterMovementComponent->StopActiveMovement();
		characterMovementComponent->SetComponentTickEnabled(false);
	}
	GetWorldTimerManager().ClearTimer(PawnMoveToTimerHandle);

	EnemyCharacter->SetLifeSpan(0.1f);
}

void AVampireAIController::PawnMoveTo()
{
	MoveToActor(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0), 5);
}
