// Louis Hobbs | 2024-2025


#include "ObjectPoolManager.h"
#include "ObjectPoolComponent.h"

// Called when the game starts or when spawned
void AObjectPoolManager::BeginPlay()
{
	Super::BeginPlay();
}

void AObjectPoolManager::InitializeObjectPool(const TSubclassOf<AActor>& TemplateObject, const int InitialObjectPoolSize)
{
	ObjectTemplate = TemplateObject;

	for (int i = 0; i < InitialObjectPoolSize; i++)
	{
		if (AActor* Object = GetWorld()->SpawnActor<
			AActor>(TemplateObject, FVector(100000.0f, 100000.0f, 0), FRotator(0, 0, 0)))
		{
			SetObjectStatus(false, Object);
			ObjectPool.Add(Object);
		}
	}
}

void AObjectPoolManager::InitializeObjectPool(UClass* TemplateObject, int InitialObjectPoolSize)
{
	for (int i = 0; i < InitialObjectPoolSize; i++)
	{
		if (AActor* Object = GetWorld()->SpawnActor<AActor>(TemplateObject))
		{
			SetObjectStatus(false, Object);
			ObjectPool.Add(Object);
		}
	}
}

AActor* AObjectPoolManager::GetObject(int StartingOffset)
{
	int ObjectPoolSize = ObjectPool.Num();
	for (int i = StartingOffset; i < ObjectPoolSize; i++)
	{
		if (ObjectPool[i]->IsHidden())
		{
			SetObjectStatus(true, ObjectPool[i]);

			if (UObjectPoolComponent* ObjectPoolComponent = ObjectPool[i]->GetComponentByClass<UObjectPoolComponent>())
			{
				ObjectPoolComponent->OnRetrieve.ExecuteIfBound();
			}

			return ObjectPool[i];
		}
	}

	InitializeObjectPool(ObjectTemplate);

	return GetObject(ObjectPoolSize);
}

void AObjectPoolManager::ReturnObject(AActor* Object)
{
	SetObjectStatus(false, Object);

	if (UObjectPoolComponent* ObjectPoolComponent = Object->GetComponentByClass<UObjectPoolComponent>())
	{
		ObjectPoolComponent->OnReturn.ExecuteIfBound();
	}
}

void AObjectPoolManager::ReturnAllObjects()
{
	int ObjectPoolSize = ObjectPool.Num();

	for (int i = 0; i < ObjectPoolSize; i++)
	{
		if (!ObjectPool[i]->IsHidden())
		{
			ReturnObject(ObjectPool[i]);			
		}
	}
}

void AObjectPoolManager::SetObjectStatus(bool bEnabled, AActor* Object)
{
	Object->SetActorHiddenInGame(!bEnabled);
	Object->SetActorTickEnabled(bEnabled);
	Object->SetActorEnableCollision(bEnabled);
}
