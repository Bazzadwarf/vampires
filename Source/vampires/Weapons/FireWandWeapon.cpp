// Fill out your copyright notice in the Description page of Project Settings.


#include "FireWandWeapon.h"

#include "Kismet/KismetMathLibrary.h"

AFireWandWeapon::AFireWandWeapon()
{
}

void AFireWandWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void AFireWandWeapon::FireWeaponAction_Implementation()
{
	if (IsValid(ProjectileTemplate) && OverlappedEnemies.Num() > 0)
	{
		FActorSpawnParameters actorSpawnParameters;
		actorSpawnParameters.Owner = this;
		actorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		actorSpawnParameters.TransformScaleMethod = ESpawnActorScaleMethod::MultiplyWithRoot;
		
		AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileTemplate, GetOwner()->GetTransform(),
																	  actorSpawnParameters);

		AActor* target = OverlappedEnemies[FMath::RandRange(0, OverlappedEnemies.Num() - 1)];
		FVector direction = UKismetMathLibrary::GetDirectionUnitVector(
			GetActorLocation(), target->GetActorLocation());
		direction.Z = 0.0;
		direction.Normalize();

		projectile->TargetDirection = direction;
	}
}
