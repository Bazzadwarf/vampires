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

	if (ProjectileTemplate && OverlappedEnemies.Num() > 0)
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

					AActor* target = OverlappedEnemies[FMath::RandRange(0, OverlappedEnemies.Num() - 1)];
					FVector direction = UKismetMathLibrary::GetDirectionUnitVector(
						GetActorLocation(), target->GetActorLocation());
					direction.Z = 0.0;
					direction.Normalize();

					IProjectilable::Execute_SetTargetDirection(projectile, direction);
				}
			}
		}
	}
}

bool AFireWandWeapon::UpgradeWeapon_Implementation()
{
	if (!Super::UpgradeWeapon_Implementation()) return false;

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
