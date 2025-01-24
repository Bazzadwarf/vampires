// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "EnemyCharacter.h"
#include "HealthComponent.h"
#include "ObjectPoolManager.h"
#include "ProjectileDataAsset.h"
#include "Components/SphereComponent.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Interfaces/Pools.h"
#include "Kismet/GameplayStatics.h"
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
	ProjectileMovement->InitialSpeed = 0;
	ProjectileMovement->MaxSpeed = 0;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	StaticMeshComponent->AttachToComponent(SphereComponent, FAttachmentTransformRules::KeepRelativeTransform);
	StaticMeshComponent->SetEnableGravity(false);
	StaticMeshComponent->SetGenerateOverlapEvents(false);
	StaticMeshComponent->SetCollisionProfileName(TEXT("NoCollision"));
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnProjectileBeginOverlap);
}

void AProjectile::SetActorHiddenInGame(bool bNewHidden)
{
	Super::SetActorHiddenInGame(bNewHidden);

	if (bNewHidden)
	{
		ResetData_Implementation();
	}
}

void AProjectile::SetTargetDirection_Implementation(FVector direction)
{
	SetActorLocation(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetCharacter()->GetActorLocation());
	SetActorRotation(FRotator(0, 0, 0));
	TargetDirection = direction;
	ProjectileMovement->SetVelocityInLocalSpace(TargetDirection * ProjectileSpeed);
}

void AProjectile::LoadDataFromDataAsset_Implementation(UProjectileDataAsset* projectileDataAsset)
{
	ProjectileSpeed = projectileDataAsset->ProjectileSpeed;
	StaticMeshComponent->SetStaticMesh(projectileDataAsset->StaticMesh);
	ProjectileSpeed = projectileDataAsset->ProjectileSpeed;
	ProjectileMovement->InitialSpeed = ProjectileSpeed;
	ProjectileMovement->MaxSpeed = ProjectileSpeed;
}

void AProjectile::ResetData_Implementation()
{
	ProjectileSpeed = NULL;
	StaticMeshComponent->SetStaticMesh(nullptr);
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

			AGameModeBase* gamemode = UGameplayStatics::GetGameMode(GetWorld());

			if (UKismetSystemLibrary::DoesImplementInterface(gamemode, UPools::StaticClass()))
			{
				if (AObjectPoolManager* objectPoolManager = IPools::Execute_GetProjectileObjectPoolManager(gamemode))
				{
					objectPoolManager->ReturnObject(this);
				}
			}
		}
	}
}
