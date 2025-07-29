// Louis Hobbs | 2024-2025

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "VampireGameInstance.generated.h"

class AWeapon;
/**
 * 
 */

UCLASS()
class VAMPIRES_API UVampireGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TSubclassOf<AWeapon> StarterWeapon;

	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UWorld> MainMenuWorld;

	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UWorld> GameWorld;
};
