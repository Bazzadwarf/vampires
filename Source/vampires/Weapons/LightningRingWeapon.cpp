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

		TArray<TEnumAsByte<EObjectTypeQuery>> traceObjectTypes;
		traceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
		
		TArray<AActor*> actorsToIgnore = TArray<AActor*>({ GetOwner() });

		TArray<AActor*> hitResults;
		
		UKismetSystemLibrary::SphereOverlapActors(GetWorld(),
			target->GetActorLocation(),
			LightingBoltRadius,
			traceObjectTypes,
			AEnemyCharacter::StaticClass(),
			actorsToIgnore,
			hitResults);

		for (AActor* EnemyHitResult : hitResults)
		{			
			UGameplayStatics::ApplyDamage(EnemyHitResult, Damage, nullptr, this, nullptr);
		}

		targetableEnemies.Remove(target);
	}
}

bool ALightningRingWeapon::UpgradeWeapon_Implementation()
{
	if (!Super::UpgradeWeapon_Implementation()) return false;

	switch (CurrentLevel)
	{
		case 1:
			LightningBolts++;
			break;
		case 2:
			LightingBoltRadius += LightingBoltRadius;
			Damage += 10;
			break;
		case 3:
			LightningBolts++;
			break;
		case 4:
			LightingBoltRadius += LightingBoltRadius;
			Damage += 20;
			break;
		case 5:
			LightningBolts++;
			break;
		case 6:
			LightingBoltRadius += LightingBoltRadius;
			Damage += 20;
			break;
		case 7:
			LightningBolts++;
			break;
		default:
			return false;
	}

	return true;
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
