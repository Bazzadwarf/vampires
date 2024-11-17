// Fill out your copyright notice in the Description page of Project Settings.


#include "VampireGameMode.h"

#include "EnemyCharacter.h"
#include "HealthComponent.h"
#include "ObjectPoolManager.h"
#include "PlayerCharacter.h"
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

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	if (AActor* object = GetEnemyObjectPoolManager()->GetObject())
	{
		AEnemyCharacter* Actor = Cast<AEnemyCharacter>(object);
		Actor->SetActorTransform(Transform);
		float CapsuleRadius = Actor->GetCapsuleComponent()->GetScaledCapsuleRadius();
		FVector Direction = SpawnLocation - PlayerCharacter->GetActorLocation();
		Direction.Normalize();
		Direction *= CapsuleRadius;
		Actor->SetActorLocation(SpawnLocation + Direction);

		if (!Actor->Controller)
		{
			Actor->SpawnDefaultController();
		}
		
		if (!Actor->GetHealthComponent()->OnDeath.IsAlreadyBound(this, &AVampireGameMode::HandleOnEnemyDeath))
		{
			Actor->GetHealthComponent()->OnDeath.AddDynamic(this, &AVampireGameMode::HandleOnEnemyDeath);
		}
		
	}
}

AObjectPoolManager* AVampireGameMode::GetEnemyObjectPoolManager()
{
	if (EnemyObjectPoolManager == nullptr)
	{
		EnemyObjectPoolManager = GetWorld()->SpawnActor<AObjectPoolManager>();
		TSubclassOf<AActor> enemyTemplate = EnemyTemplate;
		EnemyObjectPoolManager->InitializeObjectPool(enemyTemplate);
	}

	return EnemyObjectPoolManager;
}

void AVampireGameMode::IncrementEnemyDeathCount()
{
	EnemyDeathCount++;
}
