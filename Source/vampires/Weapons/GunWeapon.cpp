// Fill out your copyright notice in the Description page of Project Settings.


#include "GunWeapon.h"

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

	if (IsValid(ProjectileTemplate))
	{
		FActorSpawnParameters actorSpawnParameters;
		actorSpawnParameters.Owner = this;
		actorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		actorSpawnParameters.TransformScaleMethod = ESpawnActorScaleMethod::MultiplyWithRoot;

		AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileTemplate, GetOwner()->GetTransform(),
																	  actorSpawnParameters);
		projectile->TargetDirection = FVector(1.0f, 1.0f, 0.0f);

		projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileTemplate, GetOwner()->GetTransform(),
														 actorSpawnParameters);
		projectile->TargetDirection = FVector(-1.0f, 1.0f, 0.0f);

		projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileTemplate, GetOwner()->GetTransform(),
														 actorSpawnParameters);
		projectile->TargetDirection = FVector(1.0f, -1.0f, 0.0f);

		projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileTemplate, GetOwner()->GetTransform(),
														 actorSpawnParameters);
		projectile->TargetDirection = FVector(-1.0f, -1.0f, 0.0f);
	}
}