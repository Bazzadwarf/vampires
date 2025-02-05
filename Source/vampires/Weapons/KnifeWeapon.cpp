// Louis Hobbs | 2024-2025


#include "KnifeWeapon.h"

#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "vampires/ObjectPoolManager.h"
#include "vampires/PlayerCharacter.h"
#include "vampires/Projectile.h"
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
				}
			}
		}
	}
}
