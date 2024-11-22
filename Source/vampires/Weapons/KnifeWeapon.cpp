// Fill out your copyright notice in the Description page of Project Settings.


#include "KnifeWeapon.h"

#include "Kismet/GameplayStatics.h"
#include "vampires/PlayerCharacter.h"
#include "vampires/Projectile.h"

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
		if (IsValid(ProjectileTemplate))
		{
			FActorSpawnParameters actorSpawnParameters;
			actorSpawnParameters.Owner = this;
			actorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			actorSpawnParameters.TransformScaleMethod = ESpawnActorScaleMethod::MultiplyWithRoot;

			AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileTemplate, GetOwner()->GetTransform(),
			                                                              actorSpawnParameters);

			FVector direction = FVector(IInputable::Execute_Input_GetPreviousMovementDirection(GetOwner()), 0.0);
			direction.Normalize();
			projectile->SetTargetDirection(direction);
		}
	}	
}
