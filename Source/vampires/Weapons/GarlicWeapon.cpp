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

void AGarlicWeapon::FireWeaponAction_Implementation()
{
}

void AGarlicWeapon::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                   const FHitResult& SweepResult)
{
	if (AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(OtherActor))
	{
		FOverlappedEnemy overlappedEnemy = FOverlappedEnemy(Enemy);


		GetWorldTimerManager().SetTimer(overlappedEnemy.OverlappedTimerHandle,
		                                FTimerDelegate::CreateUObject(this, &AGarlicWeapon::GarlicFireWeaponAction,
		                                                              overlappedEnemy),
		                                WeaponCooldown,
		                                true);
		OverlappedEnemies.Add(overlappedEnemy);
	}
}

void AGarlicWeapon::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(OtherActor))
	{
		for (int i = 0; i < OverlappedEnemies.Num(); i++)
		{
			if (Enemy == OverlappedEnemies[i].OverlappedEnemyCharacter)
			{
				GetWorldTimerManager().ClearTimer(OverlappedEnemies[i].OverlappedTimerHandle);
				OverlappedEnemies.RemoveAt(i);
				return;
			}
		}
	}
}

void AGarlicWeapon::GarlicFireWeaponAction(FOverlappedEnemy EnemyCharacter)
{
	UHealthComponent* EnemyHealthComponent = EnemyCharacter.OverlappedEnemyCharacter->GetHealthComponent();

	if (!EnemyHealthComponent->GetIsDead())
	{
		if (!EnemyHealthComponent->GetIsDead())
		{
			FVector Direction = EnemyCharacter.OverlappedEnemyCharacter->GetActorLocation() - this->
				GetActorLocation();
			Direction.Normalize();
			float distance = SphereComponent->GetScaledSphereRadius();
			Direction *= distance;
			EnemyCharacter.OverlappedEnemyCharacter->SetActorLocation(
				EnemyCharacter.OverlappedEnemyCharacter->GetActorLocation() + Direction);

			AController* ownerController = nullptr;
			if (AVampireCharacter* character = Cast<AVampireCharacter>(GetOwner()))
			{
				ownerController = character->GetController();
			}

			EnemyHealthComponent->TakeDamage(EnemyCharacter.OverlappedEnemyCharacter, Damage, nullptr,
											 ownerController, this);
		}
	}
}
