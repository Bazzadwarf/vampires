// Louis Hobbs | 2024-2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObjectPoolManager.generated.h"

UCLASS()
class VAMPIRES_API AObjectPoolManager : public AActor
{
	GENERATED_BODY()

	TArray<AActor*> ObjectPool = TArray<AActor*>();

public:
	void InitializeObjectPool(TSubclassOf<AActor> Object, int InitialObjectPoolSize = 400);
	void InitializeObjectPool(UClass* Object, int InitialObjectPoolSize = 400);

	AActor* GetObject();

	void ReturnObject(AActor* object);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void SetObjectStatus(bool enabled, AActor* object);
};
