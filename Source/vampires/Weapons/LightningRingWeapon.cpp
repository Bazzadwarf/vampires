// Fill out your copyright notice in the Description page of Project Settings.


#include "LightningRingWeapon.h"
#include "Components/SphereComponent.h"
#include "vampires/EnemyCharacter.h"
#include "vampires/HealthComponent.h"

ALightningRingWeapon::ALightningRingWeapon()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	SphereComponent->SetupAttachment(RootComponent);
	SphereComponent->SetSphereRadius(1000.0f);
	Damage = 51.0f;
}

void ALightningRingWeapon::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ALightningRingWeapon::OnBeginOverlap);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &ALightningRingWeapon::OnEndOverlap);
}

void ALightningRingWeapon::FireWeaponAction_Implementation()
{
	Super::FireWeaponAction_Implementation();

	if (OverlappedEnemies.Num() > 0)
	{
		AEnemyCharacter* target = OverlappedEnemies[FMath::RandRange(0, OverlappedEnemies.Num() - 1)];
		UHealthComponent* EnemyHealthComponent = target->GetHealthComponent();
		
		AController* ownerController = nullptr;
		if (AVampireCharacter* character = Cast<AVampireCharacter>(GetOwner()))
		{
			ownerController = character->GetController();
		}
		
		EnemyHealthComponent->TakeDamage(target, Damage, nullptr, ownerController, this);
	}
}

void ALightningRingWeapon::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(OtherActor))
	{
		OverlappedEnemies.Add(Enemy);
	}
}

void ALightningRingWeapon::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(OtherActor))
	{
		OverlappedEnemies.Remove(Enemy);
	}
}
