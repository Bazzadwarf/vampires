// Louis Hobbs | 2024-2025


#include "VampireGameMode.h"

#include "EnemyCharacter.h"
#include "HealthComponent.h"
#include "ObjectPoolManager.h"
#include "PlayerCharacter.h"
#include "Projectile.h"
#include "VampirePlayerController.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

void AVampireGameMode::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	PlayerController = Cast<AVampirePlayerController>(UGameplayStatics::GetPlayerController(PlayerCharacter, 0));

	GetWorldTimerManager().SetTimer(SpawnEnemyTimerDelegate, this, &AVampireGameMode::SpawnEnemy, 1.0f, true);
}

int AVampireGameMode::GetEnemyDeathCount()
{
	return EnemyDeathCount;
}

void AVampireGameMode::HandleOnEnemyDeath(FDamageInfo damageInfo)
{
	IncrementEnemyDeathCount();
	EnemyObjectPoolManager->ReturnObject(damageInfo.DamagedActor);
	OnEnemyDeathCountIncrementDelegate.Broadcast(EnemyDeathCount);
}

void AVampireGameMode::SpawnEnemy()
{
	FVector TopLeft, TopLeftDir;
	FVector TopRight, TopRightDir;
	FVector BottomLeft, BottomLeftDir;
	FVector BottomRight, BottomRightDir;
	FVector CenterPos, CenterDir;

	FVector2d ViewportSize;
	GEngine->GameViewport->GetViewportSize(ViewportSize);

	PlayerController->DeprojectScreenPositionToWorld(0, 0, TopLeft, TopLeftDir);
	PlayerController->DeprojectScreenPositionToWorld(ViewportSize.X, 0, TopRight, TopRightDir);
	PlayerController->DeprojectScreenPositionToWorld(0, ViewportSize.Y, BottomLeft, BottomLeftDir);
	PlayerController->DeprojectScreenPositionToWorld(ViewportSize.X, ViewportSize.Y, BottomRight, BottomRightDir);
	PlayerController->DeprojectScreenPositionToWorld(ViewportSize.X / 2, ViewportSize.Y / 2, CenterPos, CenterDir);

	FVector SpawnLocation;
	switch (FMath::RandRange(0, 3))
	{
	case 0:
		SpawnLocation = FMath::Lerp(TopLeft, TopRight, FMath::RandRange(0.0f, 1.0f));
		break;
	case 1:
		SpawnLocation = FMath::Lerp(TopRight, BottomRight, FMath::RandRange(0.0f, 1.0f));
		break;
	case 2:
		SpawnLocation = FMath::Lerp(BottomRight, BottomLeft, FMath::RandRange(0.0f, 1.0f));
		break;
	case 3:
		SpawnLocation = FMath::Lerp(BottomLeft, TopLeft, FMath::RandRange(0.0f, 1.0f));
		break;
	default:
		UE_LOG(LogTemp, Warning, TEXT("Something broke"));
		break;
	}

	SpawnLocation.Z = PlayerCharacter->GetActorLocation().Z;
	FTransform Transform;
	Transform.SetLocation(SpawnLocation);

	if (AActor* enemy = GetEnemyObjectPoolManager_Implementation()->GetObject())
	{
		if (UKismetSystemLibrary::DoesImplementInterface(enemy, UEnemyable::StaticClass()) && EnemyDataAssets.Num() > 0)
		{
			IEnemyable::Execute_LoadDataFromDataAsset(enemy, EnemyDataAssets[FMath::RandRange(0, EnemyDataAssets.Num() - 1)]);
			
			enemy->SetActorTransform(Transform);
			float CapsuleRadius = IEnemyable::Execute_GetCapsuleRadius(enemy);
			FVector Direction = SpawnLocation - PlayerCharacter->GetActorLocation();
			Direction.Normalize();
			Direction *= CapsuleRadius;
			enemy->SetActorLocation(SpawnLocation + Direction);

			IEnemyable::Execute_SpawnController(enemy);

			UHealthComponent* healthComponent = IEnemyable::Execute_GetEnemyHealthComponent(enemy);
			if (!healthComponent->OnDeath.IsAlreadyBound(this, &AVampireGameMode::HandleOnEnemyDeath))
			{
				healthComponent->OnDeath.AddDynamic(this, &AVampireGameMode::HandleOnEnemyDeath);
			}
			healthComponent->ResetHealth();
		}
	}
}

AObjectPoolManager* AVampireGameMode::GetEnemyObjectPoolManager_Implementation()
{
	if (EnemyObjectPoolManager == nullptr)
	{
		EnemyObjectPoolManager = GetWorld()->SpawnActor<AObjectPoolManager>();
		TSubclassOf<AActor> enemyTemplate = EnemyTemplate;
		EnemyObjectPoolManager->InitializeObjectPool(enemyTemplate);
	}

	return EnemyObjectPoolManager;
}

AObjectPoolManager* AVampireGameMode::GetProjectileObjectPoolManager_Implementation()
{
	if (ProjectileObjectPoolManager == nullptr)
	{
		ProjectileObjectPoolManager = GetWorld()->SpawnActor<AObjectPoolManager>();
		TSubclassOf<AActor> projectileTemplate = ProjectileTemplate;
		ProjectileObjectPoolManager->InitializeObjectPool(projectileTemplate);
	}

	return ProjectileObjectPoolManager;
}

void AVampireGameMode::IncrementEnemyDeathCount()
{
	EnemyDeathCount++;
}
