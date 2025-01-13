// Fill out your copyright notice in the Description page of Project Settings.


#include "FireWandWeapon.h"

#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "vampires/ObjectPoolManager.h"
#include "vampires/Interfaces/Pools.h"
#include "vampires/Projectile.h"

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
