// Louis Hobbs | 2024-2025


#include "EnemyCharacter.h"

#include "EnemyDataAsset.h"
#include "EXPPickup.h"
#include "HealthComponent.h"
#include "ObjectPoolComponent.h"
#include "ObjectPoolManager.h"
#include "PaperFlipbookComponent.h"
#include "VampireAIController.h"
#include "VampireGameMode.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

AEnemyCharacter::AEnemyCharacter(const FObjectInitializer& ObjectInitializer)
{
	ObjectPoolComponent = CreateDefaultSubobject<UObjectPoolComponent>(TEXT("Object Pool Component"));
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetHealthComponent()->OnDamaged.AddDynamic(this, &AEnemyCharacter::OnDamaged);
	GetHealthComponent()->OnDeath.AddDynamic(this, &AEnemyCharacter::OnDeath);

	ObjectPoolComponent->OnRetrieve.BindUFunction(this, "ResetHealth");
}

void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

UBehaviorTree* AEnemyCharacter::GetBehaviorTree()
{
	return BehaviorTree;
}

void AEnemyCharacter::OnDamaged(FDamageInfo damageInfo)
{
}

void AEnemyCharacter::OnDeath(FDamageInfo damageInfo)
{
	// TODO: Replace pickup spawning with pooling
	FActorSpawnParameters actorSpawnParameters;
	actorSpawnParameters.Owner = this;
	actorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	auto spawnLocation = GetActorLocation();
	spawnLocation.Z = 75.0f;

	GetWorld()->SpawnActor<AEXPPickup>(EXPPickupTemplate, spawnLocation, FRotator::ZeroRotator,
	                                   actorSpawnParameters);
}

void AEnemyCharacter::LoadDataFromDataAsset_Implementation(UEnemyDataAsset* enemyDataAsset)
{
	if (enemyDataAsset != nullptr)
	{
		// TODO: Load more data
		StaticMeshComponent->SetStaticMesh(enemyDataAsset->StaticMesh);

		BehaviorTree = enemyDataAsset->BehaviorTree;
	}
}

void AEnemyCharacter::ResetData_Implementation()
{
	// TODO: Reset more data
	StaticMeshComponent->SetStaticMesh(nullptr);

	BehaviorTree = nullptr;
}

float AEnemyCharacter::GetCapsuleRadius_Implementation()
{
	return GetCapsuleComponent() ? GetCapsuleComponent()->GetScaledCapsuleRadius() : -1.0f;
}

void AEnemyCharacter::SpawnController_Implementation()
{
	if (!Controller)
	{
		SpawnDefaultController();
	}

	if (BehaviorTree != nullptr)
	{
		AVampireAIController* controller = Cast<AVampireAIController>(Controller);
		controller->RunBehaviorTree(BehaviorTree);
	}
}

UHealthComponent* AEnemyCharacter::GetEnemyHealthComponent_Implementation()
{
	return GetHealthComponent();
}

void AEnemyCharacter::ResetHealth()
{
	GetHealthComponent()->ResetHealth();
}
