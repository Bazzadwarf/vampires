// Louis Hobbs | 2024-2025


#include "MagicWandWeapon.h"

#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "vampires/ObjectPoolManager.h"
#include "vampires/Projectile.h"
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
				}
			}
		}
	}
}
