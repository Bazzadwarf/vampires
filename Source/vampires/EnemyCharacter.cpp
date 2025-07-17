// Louis Hobbs | 2024-2025


#include "EnemyCharacter.h"

#include "EnemyDataAsset.h"
#include "EXPPickup.h"
#include "HealthComponent.h"
#include "ObjectPoolComponent.h"
#include "ObjectPoolManager.h"
#include "VampireAIController.h"
#include "VampireGameMode.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"

AEnemyCharacter::AEnemyCharacter(const FObjectInitializer& ObjectInitializer)
{
	ObjectPoolComponent = CreateDefaultSubobject<UObjectPoolComponent>(TEXT("Object Pool Component"));

	DamageSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Damage Sphere"));
	DamageSphere->SetupAttachment(RootComponent);
	DamageSphere->SetSphereRadius(50.0f);
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetHealthComponent()->OnDamaged.AddDynamic(this, &AEnemyCharacter::OnDamaged);
	GetHealthComponent()->OnDeath.AddDynamic(this, &AEnemyCharacter::OnDeath);

	ObjectPoolComponent->OnRetrieve.BindUFunction(this, "ResetHealth");

	DamageSphere->OnComponentBeginOverlap.AddDynamic(this, &AEnemyCharacter::OnDamageBeginOverlap);
	DamageSphere->OnComponentEndOverlap.AddDynamic(this, &AEnemyCharacter::OnDamageEndOverlap);
	DamageSphere->MoveIgnoreActors.Add(this);
}

void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

UBehaviorTree* AEnemyCharacter::GetBehaviorTree()
{
	return BehaviorTree;
}

void AEnemyCharacter::OnDamaged(FDamageInfo damageInfo)
{
	// if (OnDamagedSound)
	// {
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), OnDamagedSound, GetActorLocation());
	// }

	if (OnDamagedNiagaraSystem)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, OnDamagedNiagaraSystem, GetActorLocation());
	}
}

void AEnemyCharacter::OnDeath(FDamageInfo damageInfo)
{
	if (PickupTemplate)
	{
		AGameModeBase* gamemode = UGameplayStatics::GetGameMode(GetWorld());
		if (UKismetSystemLibrary::DoesImplementInterface(gamemode, UPools::StaticClass()))
		{
			if (AObjectPoolManager* objectPoolManager = IPools::Execute_GetPickupObjectPoolManager(gamemode))
			{
				AActor* pickup = objectPoolManager->GetObject();

				if (UKismetSystemLibrary::DoesImplementInterface(pickup, UPickupable::StaticClass()))
				{
					FVector pickupLocation = GetActorLocation();
					pickup->SetActorLocation(pickupLocation);
					IPickupable::Execute_LoadDataFromDataAsset(pickup, PickupTemplate, pickupLocation);
				}
			}
		}
	}

	if (OnDeathSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), OnDeathSound, GetActorLocation());
	}

	if (OnDeathNiagaraSystem)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, OnDeathNiagaraSystem, GetActorLocation());
	}
}

void AEnemyCharacter::LoadDataFromDataAsset_Implementation(UEnemyDataAsset* enemyDataAsset)
{
	if (enemyDataAsset != nullptr)
	{
		StaticMeshComponent->SetStaticMesh(enemyDataAsset->StaticMesh);
		BehaviorTree = enemyDataAsset->BehaviorTree;
		PickupTemplate = enemyDataAsset->PickupDataAsset;
		OnDamagedSound = enemyDataAsset->OnDamagedSoundBase;
		OnDeathSound = enemyDataAsset->OnDeathSoundBase;
		OnDamagedNiagaraSystem = enemyDataAsset->OnDamagedNiagaraSystem;
		OnDeathNiagaraSystem = enemyDataAsset->OnDeathNiagaraSystem;
	}
}

void AEnemyCharacter::ResetData_Implementation()
{
	StaticMeshComponent->SetStaticMesh(nullptr);
	BehaviorTree = nullptr;
	PickupTemplate = nullptr;
	OnDamagedSound = nullptr;
	OnDeathSound = nullptr;
	OnDamagedNiagaraSystem = nullptr;
	OnDeathNiagaraSystem = nullptr;
}

float AEnemyCharacter::GetCapsuleRadius_Implementation()
{
	return GetCapsuleComponent() ? GetCapsuleComponent()->GetScaledCapsuleRadius() : -1.0f;
}

void AEnemyCharacter::SpawnController_Implementation()
{
	if (!Controller)
	{
		SpawnDefaultController();
	}

	if (BehaviorTree != nullptr)
	{
		AVampireAIController* controller = Cast<AVampireAIController>(Controller);
		controller->RunBehaviorTree(BehaviorTree);
	}
}

UHealthComponent* AEnemyCharacter::GetEnemyHealthComponent_Implementation()
{
	return GetHealthComponent();
}

void AEnemyCharacter::OnDamageBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ACharacter>(OtherActor) == UGameplayStatics::GetPlayerCharacter(GetWorld(), 0) && !Player.Contains(OtherActor))
	{
		Player.Add(OtherActor);
		
		GetWorldTimerManager().SetTimer(DamageTimerHandle, this, &AEnemyCharacter::DamagePlayer, AttackCooldown, true);
	}
}

void AEnemyCharacter::OnDamageEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Cast<ACharacter>(OtherActor) == UGameplayStatics::GetPlayerCharacter(GetWorld(), 0) && Player.Contains(OtherActor))
	{
		Player.Remove(OtherActor);

		GetWorldTimerManager().ClearTimer(DamageTimerHandle);
	}
}

void AEnemyCharacter::ResetHealth()
{
	GetHealthComponent()->ResetHealth();
}

void AEnemyCharacter::DamagePlayer()
{
	for (auto player : Player)
	{
		UGameplayStatics::ApplyDamage(player, Damage, GetController(), this, nullptr);
	}
}
