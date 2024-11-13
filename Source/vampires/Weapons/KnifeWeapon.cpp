// Fill out your copyright notice in the Description page of Project Settings.


#include "KnifeWeapon.h"

#include "Kismet/GameplayStatics.h"
#include "vampires/PlayerCharacter.h"

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

	APlayerCharacter* playerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (IsValid(ProjectileTemplate) && playerCharacter)
	{
		FActorSpawnParameters actorSpawnParameters;
		actorSpawnParameters.Owner = this;
		actorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		actorSpawnParameters.TransformScaleMethod = ESpawnActorScaleMethod::MultiplyWithRoot;

		AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileTemplate, GetOwner()->GetTransform(),
		                                                              actorSpawnParameters);

		FVector direction = FVector(playerCharacter->PreviousMovementDirection, 0.0);
		direction.Normalize();
		projectile->SetTargetDirection(direction);
	}
}
