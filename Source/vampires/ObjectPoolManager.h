// Louis Hobbs | 2024-2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObjectPoolManager.generated.h"

UCLASS()
class VAMPIRES_API AObjectPoolManager : public AActor
{
	GENERATED_BODY()

	TArray<TObjectPtr<AActor>> ObjectPool = TArray<TObjectPtr<AActor>>();
	TSubclassOf<AActor> ObjectTemplate;

public:
	void InitializeObjectPool(const TSubclassOf<AActor>& TemplateObject, int InitialObjectPoolSize = 400);
	void InitializeObjectPool(UClass* TemplateObject, int InitialObjectPoolSize = 400);

	AActor* GetObject(int StartingOffset = 0);

	void ReturnObject(AActor* Object);

	void ReturnAllObjects();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void SetObjectStatus(bool bEnabled, AActor* Object);
};
