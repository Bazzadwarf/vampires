// Louis Hobbs | 2024-2025


#include "GunWeapon.h"

#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "vampires/ObjectPoolManager.h"
#include "vampires/PlayerCharacter.h"
#include "vampires/Projectile.h"
#include "vampires/ProjectileDataAsset.h"
#include "vampires/VampirePlayerController.h"
#include "vampires/Interfaces/Pools.h"

AGunWeapon::AGunWeapon()
{
}

void AGunWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void AGunWeapon::FireWeaponAction_Implementation()
{
	Super::FireWeaponAction_Implementation();
}

bool AGunWeapon::UpgradeWeapon_Implementation()
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
		ProjectileTemplate->DamageableEnemies += 2;
		break;
	case 3:
		ProjectilesPerActivation++;
		break;
	case 4:
		Damage += 5.0f;
		break;
	case 5:
		ProjectileTemplate->DamageableEnemies += 2;
		break;
	case 6:
		Damage += 5.0f;
		ProjectileTemplate->ProjectileSpeed *= 1.50f;
		break;
	case 7:
		ProjectileTemplate->DamageableEnemies += 2;
		break;
	default:
		return false;
	}

	ResetWeaponTimer();
	return true;
}

void AGunWeapon::FireProjectile()
{
	if (ProjectileTemplate && OverlappedEnemies.Num() > 0)
	{
		AGameModeBase* Gamemode = UGameplayStatics::GetGameMode(GetWorld());

		if (UKismetSystemLibrary::DoesImplementInterface(Gamemode, UPools::StaticClass()))
		{
			if (AObjectPoolManager* ObjectPoolManager = IPools::Execute_GetProjectileObjectPoolManager(Gamemode))
			{
				FVector2d ViewportSize;
				GEngine->GameViewport->GetViewportSize(ViewportSize);

				APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(
					UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
				AVampirePlayerController* PlayerController = Cast<AVampirePlayerController>(
					UGameplayStatics::GetPlayerController(PlayerCharacter, 0));

				FVector TopLeft, TopLeftDir;
				FVector TopRight, TopRightDir;
				FVector BottomLeft, BottomLeftDir;
				FVector BottomRight, BottomRightDir;

				PlayerController->DeprojectScreenPositionToWorld(0, 0, TopLeft, TopLeftDir);
				PlayerController->DeprojectScreenPositionToWorld(ViewportSize.X, 0, TopRight, TopRightDir);
				PlayerController->DeprojectScreenPositionToWorld(0, ViewportSize.Y, BottomLeft, BottomLeftDir);
				PlayerController->DeprojectScreenPositionToWorld(ViewportSize.X, ViewportSize.Y, BottomRight,
				                                                 BottomRightDir);

				FVector ActorLocation = GetActorLocation();
				TopLeft.Z = ActorLocation.Z;
				TopRight.Z = ActorLocation.Z;
				BottomLeft.Z = ActorLocation.Z;
				BottomRight.Z = ActorLocation.Z;

				AActor* projectile = ObjectPoolManager->GetObject();
				SpawnProjectile(projectile, UKismetMathLibrary::GetDirectionUnitVector(ActorLocation, TopLeft));
				projectile = ObjectPoolManager->GetObject();
				SpawnProjectile(projectile, UKismetMathLibrary::GetDirectionUnitVector(ActorLocation, TopRight));
				projectile = ObjectPoolManager->GetObject();
				SpawnProjectile(projectile, UKismetMathLibrary::GetDirectionUnitVector(ActorLocation, BottomLeft));
				projectile = ObjectPoolManager->GetObject();
				SpawnProjectile(projectile, UKismetMathLibrary::GetDirectionUnitVector(ActorLocation, BottomRight));

				Super::FireProjectile();
			}
		}
	}
}

void AGunWeapon::SpawnProjectile(AActor* Projectile, const FVector& Direction)
{
	if (UKismetSystemLibrary::DoesImplementInterface(Projectile, UProjectilable::StaticClass()))
	{
		IProjectilable::Execute_LoadDataFromDataAsset(Projectile, ProjectileTemplate);
		Projectile->SetOwner(this);
		IProjectilable::Execute_SetTargetDirection(Projectile, Direction);
	}
}
