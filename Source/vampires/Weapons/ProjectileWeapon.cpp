// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileWeapon.h"

#include "vampires/EnemyCharacter.h"

AProjectileWeapon::AProjectileWeapon()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	SphereComponent->SetupAttachment(RootComponent);
	SphereComponent->SetSphereRadius(1000.0f);
}

void AProjectileWeapon::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AProjectileWeapon::OnWeaponBeginOverlap);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &AProjectileWeapon::OnWeaponEndOverlap);
}

void AProjectileWeapon::OnWeaponBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                             UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(OtherActor))
	{
		OverlappedEnemies.Add(Enemy);
	}
}

void AProjectileWeapon::OnWeaponEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(OtherActor))
	{
		OverlappedEnemies.Remove(Enemy);
	}
}

void AProjectileWeapon::OnProjectileBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(OtherActor))
	{
		UHealthComponent* EnemyHealthComponent = Enemy->GetHealthComponent();

		if (!EnemyHealthComponent->GetIsDead())
		{
			AController* ownerController = nullptr;
			if (AVampireCharacter* character = Cast<AVampireCharacter>(GetOwner()))
			{
				ownerController = character->GetController();
			}

			EnemyHealthComponent->TakeDamage(Enemy, Damage, nullptr, ownerController, this);

			OverlappedComponent->GetAttachmentRootActor()->Destroy();
		}
	}
}
