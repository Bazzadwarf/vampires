// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"

#include "VampireGameMode.h"
#include "Kismet/GameplayStatics.h"

AEnemyCharacter::AEnemyCharacter(const FObjectInitializer& ObjectInitializer)
{
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetHealthComponent()->OnDamaged.BindUFunction(this, "OnDamaged");
	GetHealthComponent()->OnDeath.BindUFunction(this, "OnDeath");
}

void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

UBehaviorTree* AEnemyCharacter::GetBehaviorTree()
{
	return BehaviorTree;
}

void AEnemyCharacter::OnDamaged()
{
}

void AEnemyCharacter::OnDeath()
{
	//if (IsValid(EXPPickupTemplate))
	//{
		FActorSpawnParameters actorSpawnParameters;
		actorSpawnParameters.Owner = this;
		actorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		actorSpawnParameters.TransformScaleMethod = ESpawnActorScaleMethod::MultiplyWithRoot;

		GetWorld()->SpawnActor<AEXPPickup>(EXPPickupTemplate, GetActorLocation(), FRotator::ZeroRotator,
		                                   actorSpawnParameters);

		AVampireGameMode* gamemode = Cast<AVampireGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		gamemode->IncrementEnemyDeathCount();
	//}
}
