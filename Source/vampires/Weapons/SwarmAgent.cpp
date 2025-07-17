// Louis Hobbs | 2024-2025


#include "SwarmAgent.h"

#include "Components/SphereComponent.h"
#include "vampires/EnemyCharacter.h"
#include "vampires/HealthComponent.h"
#include "vampires/Weapon.h"


// Sets default values
ASwarmAgent::ASwarmAgent()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	SetRootComponent(SphereComponent);
	SphereComponent->SetSphereRadius(50.0f);
	SphereComponent->SetCollisionProfileName(TEXT("Weapon"));

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	StaticMeshComponent->AttachToComponent(SphereComponent, FAttachmentTransformRules::KeepRelativeTransform);
	StaticMeshComponent->SetEnableGravity(false);
	StaticMeshComponent->SetGenerateOverlapEvents(false);
	StaticMeshComponent->SetCollisionProfileName(TEXT("NoCollision"));
}

// Called when the game starts or when spawned
void ASwarmAgent::BeginPlay()
{
	Super::BeginPlay();

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ASwarmAgent::OnSwarmAgentBeginOverlap);
}

void ASwarmAgent::OnSwarmAgentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                           UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                           const FHitResult& SweepResult)
{
	if (AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(OtherActor))
	{
		UHealthComponent* EnemyHealthComponent = Enemy->GetHealthComponent();

		if (!EnemyHealthComponent->GetIsDead())
		{
			if (AVampireCharacter* character = Cast<AVampireCharacter>(GetOwner()))
			{
				AController* ownerController = character->GetController();
				AWeapon* ownerWeapon = Cast<AWeapon>(GetOwner());
				EnemyHealthComponent->TakeDamage(Enemy, ownerWeapon->Damage, nullptr, ownerController, this);
			}
		}
	}
}
