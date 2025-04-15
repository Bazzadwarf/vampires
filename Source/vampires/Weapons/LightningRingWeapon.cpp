// Louis Hobbs | 2024-2025


#include "LightningRingWeapon.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "vampires/EnemyCharacter.h"
#include "vampires/HealthComponent.h"

ALightningRingWeapon::ALightningRingWeapon()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	SphereComponent->SetupAttachment(RootComponent);
	SphereComponent->SetSphereRadius(1000.0f);
	SphereComponent->SetCollisionProfileName(TEXT("Weapon"));
	
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

	TArray<AEnemyCharacter*> targetableEnemies = OverlappedEnemies;

	for (int i  = 0; i < LightningBolts && targetableEnemies.Num() > 0; i++)
	{
		AEnemyCharacter* target = targetableEnemies[FMath::RandRange(0, targetableEnemies.Num() - 1)];

		TArray<AActor*> actorsToIgnore = TArray<AActor*>({ GetOwner() });
		TArray<FHitResult> hitResults;
		UKismetSystemLibrary::SphereTraceMultiByProfile(GetWorld(),
			target->GetActorLocation(),
			target->GetActorLocation(),
			500.0f,
			FName(TEXT("Funny")),
			false,
			actorsToIgnore,
			EDrawDebugTrace::ForDuration,
			hitResults,
			true);

		for (FHitResult EnemyHitResult : hitResults)
		{			
			UGameplayStatics::ApplyDamage(EnemyHitResult.GetActor(), Damage, nullptr, this, nullptr);
		}

		targetableEnemies.Remove(target);
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
