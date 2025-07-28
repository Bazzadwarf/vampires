// Louis Hobbs | 2024-2025


#include "MagicWandWeapon.h"

#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "vampires/ObjectPoolManager.h"
#include "vampires/Projectile.h"
#include "vampires/ProjectileDataAsset.h"
#include "vampires/Interfaces/Pools.h"

AMagicWandWeapon::AMagicWandWeapon()
{
}

void AMagicWandWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void AMagicWandWeapon::FireWeaponAction_Implementation()
{
	Super::FireWeaponAction_Implementation();
}

bool AMagicWandWeapon::UpgradeWeapon_Implementation()
{
	if (!Super::UpgradeWeapon_Implementation())
	{
		return false;
	}

	switch (CurrentLevel)
	{
	case 1:
		ProjectilesPerActivation++;
		break;
	case 2:
		WeaponCooldown -= 0.2;
		break;
	case 3:
		ProjectilesPerActivation++;
		break;
	case 4:
		Damage += 10;
		break;
	case 5:
		ProjectilesPerActivation++;
		break;
	case 6:
		ProjectileTemplate->DamageableEnemies++;
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

void AMagicWandWeapon::FireProjectile()
{
	if (ProjectileTemplate && OverlappedEnemies.Num() > 0)
	{
		float Distance = 0.0f;

		if (AActor* nearestActor = UGameplayStatics::FindNearestActor(GetActorLocation(), OverlappedEnemies, Distance))
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

						FVector Direction = UKismetMathLibrary::GetDirectionUnitVector(
							GetActorLocation(), nearestActor->GetActorLocation());
						Direction.Z = 0.0;
						Direction.Normalize();

						IProjectilable::Execute_SetTargetDirection(Projectile, Direction);
					}

					Super::FireProjectile();
				}
			}
		}
	}
}
