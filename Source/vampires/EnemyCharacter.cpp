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

void AEnemyCharacter::OnDamaged(FDamageInfo DamageInfo)
{
	if (OnDamagedSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), OnDamagedSound, GetActorLocation());
	}

	if (OnDamagedNiagaraSystem)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, OnDamagedNiagaraSystem, GetActorLocation());
	}
}

void AEnemyCharacter::OnDeath(FDamageInfo DamageInfo)
{
	if (PickupTemplate)
	{
		AGameModeBase* Gamemode = UGameplayStatics::GetGameMode(GetWorld());
		if (UKismetSystemLibrary::DoesImplementInterface(Gamemode, UPools::StaticClass()))
		{
			if (AObjectPoolManager* ObjectPoolManager = IPools::Execute_GetPickupObjectPoolManager(Gamemode))
			{
				AActor* Pickup = ObjectPoolManager->GetObject();

				if (UKismetSystemLibrary::DoesImplementInterface(Pickup, UPickupable::StaticClass()))
				{
					FVector PickupLocation = GetActorLocation();
					Pickup->SetActorLocation(PickupLocation);
					IPickupable::Execute_LoadDataFromDataAsset(Pickup, PickupTemplate, PickupLocation);
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

void AEnemyCharacter::LoadDataFromDataAsset_Implementation(UEnemyDataAsset* EnemyDataAsset)
{
	if (EnemyDataAsset != nullptr)
	{
		StaticMeshComponent->SetStaticMesh(EnemyDataAsset->StaticMesh);
		BehaviorTree = EnemyDataAsset->BehaviorTree;
		PickupTemplate = EnemyDataAsset->PickupDataAsset;
		OnDamagedSound = EnemyDataAsset->OnDamagedSoundBase;
		OnDeathSound = EnemyDataAsset->OnDeathSoundBase;
		OnDamagedNiagaraSystem = EnemyDataAsset->OnDamagedNiagaraSystem;
		OnDeathNiagaraSystem = EnemyDataAsset->OnDeathNiagaraSystem;
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

	if (AVampireAIController* VampireAIController = Cast<AVampireAIController>(Controller); VampireAIController &&
		BehaviorTree)
	{
		VampireAIController->RunBehaviorTree(BehaviorTree);
	}
}

UHealthComponent* AEnemyCharacter::GetEnemyHealthComponent_Implementation()
{
	return GetHealthComponent();
}

void AEnemyCharacter::OnDamageBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                           UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                           const FHitResult& SweepResult)
{
	if (Cast<ACharacter>(OtherActor) == UGameplayStatics::GetPlayerCharacter(GetWorld(), 0) && !Player.
		Contains(OtherActor))
	{
		Player.Add(OtherActor);

		GetWorldTimerManager().SetTimer(DamageTimerHandle, this, &AEnemyCharacter::DamagePlayer, AttackCooldown, true);
	}
}

void AEnemyCharacter::OnDamageEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                         UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Cast<ACharacter>(OtherActor) == UGameplayStatics::GetPlayerCharacter(GetWorld(), 0) && Player.
		Contains(OtherActor))
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
	for (auto DamagedPlayer : Player)
	{
		UGameplayStatics::ApplyDamage(DamagedPlayer, Damage, GetController(), this, nullptr);
	}
}
