// Louis Hobbs | 2024-2025


#include "FireWandWeapon.h"

#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "vampires/ObjectPoolManager.h"
#include "vampires/Interfaces/Pools.h"
#include "vampires/Projectile.h"
#include "vampires/ProjectileDataAsset.h"

AFireWandWeapon::AFireWandWeapon()
{
}

void AFireWandWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void AFireWandWeapon::FireWeaponAction_Implementation()
{
	Super::FireWeaponAction_Implementation();
}

bool AFireWandWeapon::UpgradeWeapon_Implementation()
{
	if (!Super::UpgradeWeapon_Implementation())
	{
		return false;
	}

	switch (CurrentLevel)
	{
	case 1:
		Damage += 10;
		break;
	case 2:
		Damage += 10;
		ProjectileTemplate->ProjectileSpeed *= 1.2f;
		break;
	case 3:
		Damage += 10;
		break;
	case 4:
		Damage += 10;
		ProjectileTemplate->ProjectileSpeed *= 1.2f;
		break;
	case 5:
		Damage += 10;
		break;
	case 6:
		Damage += 10;
		ProjectileTemplate->ProjectileSpeed *= 1.2f;
		break;
	case 7:
		Damage += 10;
		break;
	default:
		return false;
	}

	ResetWeaponTimer();
	return true;
}

void AFireWandWeapon::FireProjectile()
{
	if (ProjectileTemplate && OverlappedEnemies.Num() > 0)
	{
		AGameModeBase* Gamemode = UGameplayStatics::GetGameMode(GetWorld());

		if (UKismetSystemLibrary::DoesImplementInterface(Gamemode, UPools::StaticClass()))
		{
			if (AObjectPoolManager* ObjectPoolManager = IPools::Execute_GetProjectileObjectPoolManager(Gamemode))
			{
				AActor* Projectile = ObjectPoolManager->GetObject();

				if (UKismetSystemLibrary::DoesImplementInterface(Projectile, UProjectilable::StaticClass()))
				{
					IProjectilable::Execute_LoadDataFromDataAsset(Projectile, ProjectileTemplate);
					Projectile->SetOwner(this);

					AActor* Target = OverlappedEnemies[FMath::RandRange(0, OverlappedEnemies.Num() - 1)];
					FVector Direction = UKismetMathLibrary::GetDirectionUnitVector(
						GetActorLocation(), Target->GetActorLocation());
					Direction.Z = 0.0;
					Direction.Normalize();

					IProjectilable::Execute_SetTargetDirection(Projectile, Direction);
				}

				Super::FireProjectile();
			}
		}
	}
}
