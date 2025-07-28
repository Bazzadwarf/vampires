// Louis Hobbs | 2024-2025


#include "LightningRingWeapon.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "vampires/EnemyCharacter.h"
#include "NiagaraFunctionLibrary.h"

ALightningRingWeapon::ALightningRingWeapon()
{
	Damage = 51.0f;
}

void ALightningRingWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void ALightningRingWeapon::FireWeaponAction_Implementation()
{
	Super::FireWeaponAction_Implementation();

	TArray<AActor*> TargetableEnemies = OverlappedEnemies;

	for (int i = 0; i < LightningBolts && TargetableEnemies.Num() > 0; i++)
	{
		AActor* Target = TargetableEnemies[FMath::RandRange(0, TargetableEnemies.Num() - 1)];

		TArray<TEnumAsByte<EObjectTypeQuery>> traceObjectTypes;
		traceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

		TArray<AActor*> ActorsToIgnore = TArray<AActor*>({GetOwner()});

		TArray<AActor*> HitResults;

		UKismetSystemLibrary::SphereOverlapActors(GetWorld(),
		                                          Target->GetActorLocation(),
		                                          LightingBoltRadius,
		                                          traceObjectTypes,
		                                          AEnemyCharacter::StaticClass(),
		                                          ActorsToIgnore,
		                                          HitResults);

		if (LightningEffectSystem)
		{
			float Scale = FMath::FloorToFloat((CurrentLevel + 2.0f) / 2.0f);
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, LightningEffectSystem, Target->GetActorLocation(),
			                                               GetActorRotation(), FVector(Scale));
		}

		for (AActor* EnemyHitResult : HitResults)
		{
			UGameplayStatics::ApplyDamage(EnemyHitResult, Damage, nullptr, this, nullptr);
		}

		TargetableEnemies.Remove(Target);
	}
}

bool ALightningRingWeapon::UpgradeWeapon_Implementation()
{
	if (!Super::UpgradeWeapon_Implementation())
	{
		return false;
	}

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
