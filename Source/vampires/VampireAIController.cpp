// Louis Hobbs | 2024-2025


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
	DefaultBlackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard"));
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
		DefaultBlackboard->SetValueAsVector("PlayerLocation", PlayerCharacter->GetActorLocation());
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

	if (UBehaviorTree* BT = EnemyCharacter->GetBehaviorTree())
	{
		DefaultBlackboard->InitializeBlackboard(*BT->BlackboardAsset);
		BehaviorTree->StartTree(*BT);
		DefaultBlackboard->SetValueAsObject("SelfActor", EnemyCharacter);

		if (PlayerCharacter)
		{
			DefaultBlackboard->SetValueAsObject("Player", PlayerCharacter);
		}
	}
}

void AVampireAIController::OnDamaged(FDamageInfo Info)
{
	if (EnemyCharacter->GetHealthComponent()->GetCurrentHealth() > 0.0f)
	{
		// TODO: Something
	}
}

void AVampireAIController::OnDeath(FDamageInfo Info)
{
	EnemyCharacter->OnDeath(Info);
}

void AVampireAIController::PawnMoveTo()
{
	MoveToActor(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0), 5);
}
