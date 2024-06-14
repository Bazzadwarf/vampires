// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"

AEnemyCharacter::AEnemyCharacter(const FObjectInitializer& ObjectInitializer)
{
	GetHealthComponent()->OnDamaged.BindUFunction(this, "OnDamaged");
	GetHealthComponent()->OnDeath.BindUFunction(this, "OnDeath");
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
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
}
