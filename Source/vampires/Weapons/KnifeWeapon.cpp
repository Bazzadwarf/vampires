// Louis Hobbs | 2024-2025


#include "KnifeWeapon.h"

#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "vampires/ObjectPoolManager.h"
#include "vampires/PlayerCharacter.h"
#include "vampires/Projectile.h"
#include "vampires/ProjectileDataAsset.h"
#include "vampires/Interfaces/Pools.h"

AKnifeWeapon::AKnifeWeapon()
{
}

void AKnifeWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void AKnifeWeapon::FireWeaponAction_Implementation()
{
	Super::FireWeaponAction_Implementation();
}

bool AKnifeWeapon::UpgradeWeapon_Implementation()
{
	if (!Super::UpgradeWeapon_Implementation()) return false;

	switch (CurrentLevel)
	{
		case 1:
			ProjectilesPerActivation++;
			break;
		case 2:
			ProjectilesPerActivation++;
			Damage += 5.0f;
			break;
		case 3:
			ProjectilesPerActivation++;
			break;
		case 4:
			ProjectileTemplate->DamageableEnemies++;
			break;
		case 5:
			ProjectilesPerActivation++;
			break;
		case 6:
			ProjectilesPerActivation++;
			Damage += 5.0f;
			break;
		case 7:
			ProjectileTemplate->DamageableEnemies++;
			break;
		default:
			return false;
	}
	
	return true;
}

void AKnifeWeapon::FireProjectile()
{
	if (UKismetSystemLibrary::DoesImplementInterface(GetOwner(), UInputable::StaticClass()))
	{
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

						FVector direction = FVector(IInputable::Execute_Input_GetPreviousMovementDirection(GetOwner()),
						                            0.0);
						direction.Normalize();

						IProjectilable::Execute_SetTargetDirection(projectile, direction);
					}

					Super::FireProjectile();
				}
			}
		}
	}
}
