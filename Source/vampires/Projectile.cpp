// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "EnemyCharacter.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Weapons/ProjectileWeapon.h"

// Sets default values
AProjectile::AProjectile()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	SetRootComponent(SphereComponent);
	SphereComponent->SetSphereRadius(50.0f);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement->ProjectileGravityScale = 0.0f;
	ProjectileMovement->Friction = 0.0f;
	ProjectileMovement->bIsSliding = true;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnProjectileBeginOverlap);
	ProjectileMovement->InitialSpeed = ProjectileSpeed;
	ProjectileMovement->MaxSpeed = ProjectileSpeed;
}

void AProjectile::SetTargetDirection(FVector direction)
{
	TargetDirection = direction;
	ProjectileMovement->SetVelocityInLocalSpace(TargetDirection * ProjectileSpeed);
}

void AProjectile::OnProjectileBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
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
			
			AProjectileWeapon* ownerWeapon = Cast<AProjectileWeapon>(GetOwner());
			EnemyHealthComponent->TakeDamage(Enemy, ownerWeapon->Damage, nullptr, ownerController, this);

			OverlappedComponent->GetAttachmentRootActor()->Destroy();
		}
	}
}
