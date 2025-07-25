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
	if (!Super::UpgradeWeapon_Implementation()) return false;

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
		float distance = 0.0f;
		AActor* nearestActor = UGameplayStatics::FindNearestActor(GetActorLocation(), OverlappedEnemies, distance);

		if (nearestActor)
		{
			AGameModeBase* gamemode = UGameplayStatics::GetGameMode(GetWorld());

			if (UKismetSystemLibrary::DoesImplementInterface(gamemode, UPools::StaticClass()))
			{
				if (AObjectPoolManager* objectPoolManager = IPools::Execute_GetProjectileObjectPoolManager(gamemode))
				{
					AActor* projectile = objectPoolManager->GetObject();

					if (UKismetSystemLibrary::DoesImplementInterface(projectile, UProjectilable::StaticClass()))
					{
						IProjectilable::Execute_LoadDataFromDataAsset(projectile, ProjectileTemplate);
						projectile->SetOwner(this);

						FVector direction = UKismetMathLibrary::GetDirectionUnitVector(
							GetActorLocation(), nearestActor->GetActorLocation());
						direction.Z = 0.0;
						direction.Normalize();

						IProjectilable::Execute_SetTargetDirection(projectile, direction);
					}

					Super::FireProjectile();
				}
			}
		}
	}
}
