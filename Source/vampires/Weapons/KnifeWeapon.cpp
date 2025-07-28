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

						FVector Direction = FVector(IInputable::Execute_Input_GetPreviousMovementDirection(GetOwner()),
						                            0.0);
						Direction.Normalize();

						IProjectilable::Execute_SetTargetDirection(Projectile, Direction);
					}

					Super::FireProjectile();
				}
			}
		}
	}
}
