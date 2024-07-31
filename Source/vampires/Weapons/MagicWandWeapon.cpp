// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicWandWeapon.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "vampires/EnemyCharacter.h"

AMagicWandWeapon::AMagicWandWeapon()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	SphereComponent->SetupAttachment(RootComponent);
	SphereComponent->SetSphereRadius(1000.0f);
}

void AMagicWandWeapon::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AMagicWandWeapon::OnWeaponBeginOverlap);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &AMagicWandWeapon::OnWeaponEndOverlap);
}

void AMagicWandWeapon::FireWeaponAction_Implementation()
{
	Super::FireWeaponAction_Implementation();

	if (IsValid(ProjectileTemplate))
	{
		float distance = 0.0f;
		AActor* nearestActor = UGameplayStatics::FindNearestActor(GetActorLocation(), OverlappedEnemies, distance);

		if (nearestActor)
		{
			FActorSpawnParameters actorSpawnParameters;
			actorSpawnParameters.Owner = this;
			actorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			actorSpawnParameters.TransformScaleMethod = ESpawnActorScaleMethod::MultiplyWithRoot;

			AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileTemplate, GetTransform(),
			                                                              actorSpawnParameters);
			FVector direction = UKismetMathLibrary::GetDirectionUnitVector(
				GetActorLocation(), nearestActor->GetActorLocation());
			direction.Z = 0.0;
			direction.Normalize();
			projectile->TargetDirection = direction;
		}
	}
}

void AMagicWandWeapon::OnWeaponBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                            const FHitResult& SweepResult)
{
	if (AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(OtherActor))
	{
		OverlappedEnemies.Add(Enemy);
	}
}

void AMagicWandWeapon::OnWeaponEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                          UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(OtherActor))
	{
		OverlappedEnemies.Remove(Enemy);
	}
}

void AMagicWandWeapon::OnProjectileBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                                const FHitResult& SweepResult)
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
