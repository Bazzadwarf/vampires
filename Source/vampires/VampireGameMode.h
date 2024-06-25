// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyCharacter.h"
#include "PlayerCharacter.h"
#include "VampirePlayerController.h"
#include "GameFramework/GameMode.h"
#include "VampireGameMode.generated.h"

/**
 * 
 */
UCLASS()
class VAMPIRES_API AVampireGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AEnemyCharacter> EnemyTemplate;

private:
	APlayerCharacter* PlayerCharacter;

	AVampirePlayerController* PlayerController;

	FTimerHandle SpawnEnemyTimerDelegate;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void SpawnEnemy();
};
