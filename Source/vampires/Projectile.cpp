// Louis Hobbs | 2024-2025


#include "Projectile.h"

#include "EnemyCharacter.h"
#include "HealthComponent.h"
#include "NiagaraComponent.h"
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
	SphereComponent->SetCollisionProfileName(TEXT("Weapon"));

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

	NiagaraRibbonComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara Ribbon Component"));
	NiagaraRibbonComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	NiagaraRibbonComponent->DeactivateImmediate();
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
		GetWorldTimerManager().ClearTimer(ProjectileLifetimeTimerHandle);
	}
	else
	{
		GetWorldTimerManager().SetTimer(ProjectileLifetimeTimerHandle, this, &AProjectile::ReturnProjectileToPool, ProjectileLifespan, true);		
	}
}

void AProjectile::SetTargetDirection_Implementation(FVector Direction)
{
	SetActorLocation(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetCharacter()->GetActorLocation());
	SetActorRotation(FRotator(0, 0, 0));
	TargetDirection = Direction;
	ProjectileMovement->SetVelocityInLocalSpace(TargetDirection * ProjectileSpeed);
}

void AProjectile::LoadDataFromDataAsset_Implementation(UProjectileDataAsset* ProjectileDataAsset)
{
	ProjectileSpeed = ProjectileDataAsset->ProjectileSpeed;
	StaticMeshComponent->SetStaticMesh(ProjectileDataAsset->StaticMesh);
	ProjectileSpeed = ProjectileDataAsset->ProjectileSpeed;
	ProjectileMovement->InitialSpeed = ProjectileSpeed;
	ProjectileMovement->MaxSpeed = ProjectileSpeed;
	RemainingDamageableEnemies = ProjectileDataAsset->DamageableEnemies;
	NiagaraRibbonComponent->SetAsset(ProjectileDataAsset->NiagaraRibbonSystem);
	NiagaraRibbonComponent->ActivateSystem();
}

void AProjectile::ResetData_Implementation()
{
	ProjectileSpeed = NULL;
	StaticMeshComponent->SetStaticMesh(nullptr);
	RemainingDamageableEnemies = 1;
	NiagaraRibbonComponent->DeactivateImmediate();
	NiagaraRibbonComponent->SetAsset(nullptr);
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
			EnemyHealthComponent->TakeDamage(Enemy, ownerWeapon->GetDamage(), nullptr, ownerController, this);

			RemainingDamageableEnemies--;

			if (RemainingDamageableEnemies == 0)
			{
				ReturnProjectileToPool();
			}
		}
	}
}

void AProjectile::ReturnProjectileToPool()
{
	AGameModeBase* gamemode = UGameplayStatics::GetGameMode(GetWorld());

	if (UKismetSystemLibrary::DoesImplementInterface(gamemode, UPools::StaticClass()))
	{
		if (AObjectPoolManager* objectPoolManager =
			IPools::Execute_GetProjectileObjectPoolManager(gamemode))
		{
			objectPoolManager->ReturnObject(this);
		}
	}
}
