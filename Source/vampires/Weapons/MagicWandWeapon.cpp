// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicWandWeapon.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "vampires/Projectile.h"

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

	if (IsValid(ProjectileTemplate))
	{
		float distance = 0.0f;
		AActor* nearestActor = UGameplayStatics::FindNearestActor(GetActorLocation(), OverlappedEnemies, distance);

		if (nearestActor)
		{
			FActorSpawnParameters actorSpawnParameters;
			actorSpawnParameters.Owner = this;
			actorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			actorSpawnParameters.TransformScaleMethod = ESpawnActorScaleMethod::MultiplyWithRoot;
			
			AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileTemplate, GetOwner()->GetTransform(),
			                                                              actorSpawnParameters);
			FVector direction = UKismetMathLibrary::GetDirectionUnitVector(
				GetActorLocation(), nearestActor->GetActorLocation());
			direction.Z = 0.0;
			direction.Normalize();
			projectile->SetTargetDirection(direction);
		}
	}
}
