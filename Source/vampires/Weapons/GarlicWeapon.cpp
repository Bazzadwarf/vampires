// Fill out your copyright notice in the Description page of Project Settings.


#include "GarlicWeapon.h"

AGarlicWeapon::AGarlicWeapon()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	SphereComponent->SetupAttachment(RootComponent);
	SphereComponent->SetSphereRadius(150.0f);
	Damage = 51.0f;
}

void AGarlicWeapon::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AGarlicWeapon::OnBeginOverlap);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &AGarlicWeapon::OnEndOverlap);
}

void AGarlicWeapon::FireWeaponAction()
{
	TArray<AEnemyCharacter*> OverlappedEnemiesCache = OverlappedEnemies;

	for (int i = 0; i < OverlappedEnemiesCache.Num(); i++)
	{
		bool deadCheck = false;
		UHealthComponent* EnemyHealthComponent = OverlappedEnemiesCache[i]->GetHealthComponent();

		if (!EnemyHealthComponent->GetIsDead())
		{
			FVector Direction = OverlappedEnemiesCache[i]->GetActorLocation() - this->GetActorLocation();
			Direction.Normalize();
			float distance = SphereComponent->GetScaledSphereRadius();
			Direction *= distance;
			OverlappedEnemiesCache[i]->SetActorLocation(OverlappedEnemiesCache[i]->GetActorLocation() + Direction);

			if (EnemyHealthComponent->GetCurrentHealth() < Damage)
			{
				deadCheck = true;
			}
			
			AController* ownerController = nullptr;
			if (AVampireCharacter* character = Cast<AVampireCharacter>(GetOwner()))
			{
				ownerController = character->GetController();
			}

			EnemyHealthComponent->TakeDamage(OverlappedEnemiesCache[i], Damage, nullptr, ownerController, this);
		}

		if (deadCheck)
		{
			i -= 1;
		}
	}

	Super::FireWeaponAction();
}

void AGarlicWeapon::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                   const FHitResult& SweepResult)
{
	if (AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(OtherActor))
	{
		OverlappedEnemies.Add(Enemy);
	}
}

void AGarlicWeapon::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(OtherActor))
	{
		OverlappedEnemies.Remove(Enemy);
	}
}
