// Louis Hobbs | 2024-2025


#include "ObjectPoolManager.h"
#include "ObjectPoolComponent.h"

// Called when the game starts or when spawned
void AObjectPoolManager::BeginPlay()
{
	Super::BeginPlay();
}

void AObjectPoolManager::InitializeObjectPool(TSubclassOf<AActor> Object, const int InitialObjectPoolSize)
{
	for (int i = 0; i < InitialObjectPoolSize; i++)
	{
		if (AActor* object = GetWorld()->SpawnActor<AActor>(Object, FVector(100000.0f, 100000.0f, 0), FRotator(0, 0, 0)))
		{
			SetObjectStatus(false, object);
			ObjectPool.Add(object);
		}
	}
}

void AObjectPoolManager::InitializeObjectPool(UClass* Object, int InitialObjectPoolSize)
{
	for (int i = 0; i < InitialObjectPoolSize; i++)
	{
		if (AActor* object = GetWorld()->SpawnActor<AActor>(Object))
		{
			SetObjectStatus(false, object);
			ObjectPool.Add(object);
		}
	}
}

AActor* AObjectPoolManager::GetObject()
{
	for (AActor* object : ObjectPool)
	{
		if (object->IsHidden())
		{
			SetObjectStatus(true, object);

			if (UObjectPoolComponent* objectPoolComponent = object->GetComponentByClass<UObjectPoolComponent>())
			{
				objectPoolComponent->OnRetrieve.ExecuteIfBound();
			}

			return object;
		}
	}

	return nullptr;
}

void AObjectPoolManager::ReturnObject(AActor* object)
{
	SetObjectStatus(false, object);

	if (UObjectPoolComponent* objectPoolComponent = object->GetComponentByClass<UObjectPoolComponent>())
	{
		objectPoolComponent->OnReturn.ExecuteIfBound();
	}
}

void AObjectPoolManager::SetObjectStatus(bool enabled, AActor* object)
{
	object->SetActorHiddenInGame(!enabled);
	object->SetActorTickEnabled(enabled);
	object->SetActorEnableCollision(enabled);
}
