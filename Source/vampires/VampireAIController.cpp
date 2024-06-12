// Fill out your copyright notice in the Description page of Project Settings.


#include "VampireAIController.h"

AVampireAIController::AVampireAIController(const FObjectInitializer& object_initializer)
{
}

void AVampireAIController::BeginPlay()
{
	Super::BeginPlay();
}

void AVampireAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AVampireAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void AVampireAIController::OnDamaged(FDamageInfo info)
{
}

void AVampireAIController::OnDeath(FDamageInfo info)
{
}
