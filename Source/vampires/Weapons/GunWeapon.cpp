// Fill out your copyright notice in the Description page of Project Settings.


#include "GunWeapon.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "vampires/PlayerCharacter.h"
#include "vampires/Projectile.h"
#include "vampires/VampirePlayerController.h"

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
		FVector2d ViewportSize;
		GEngine->GameViewport->GetViewportSize(ViewportSize);

		APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		AVampirePlayerController* PlayerController = Cast<AVampirePlayerController>(
			UGameplayStatics::GetPlayerController(PlayerCharacter, 0));
		
		FVector TopLeft, TopLeftDir;
		FVector TopRight, TopRightDir;
		FVector BottomLeft, BottomLeftDir;
		FVector BottomRight, BottomRightDir;

		PlayerController->DeprojectScreenPositionToWorld(0, 0, TopLeft, TopLeftDir);
		PlayerController->DeprojectScreenPositionToWorld(ViewportSize.X, 0, TopRight, TopRightDir);
		PlayerController->DeprojectScreenPositionToWorld(0, ViewportSize.Y, BottomLeft, BottomLeftDir);
		PlayerController->DeprojectScreenPositionToWorld(ViewportSize.X, ViewportSize.Y, BottomRight, BottomRightDir);
		
		FVector actorLocation = GetActorLocation();
		TopLeft.Z = actorLocation.Z;
		TopRight.Z = actorLocation.Z;
		BottomLeft.Z = actorLocation.Z;
		BottomRight.Z = actorLocation.Z;
		
		FActorSpawnParameters actorSpawnParameters;
		actorSpawnParameters.Owner = this;
		actorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		actorSpawnParameters.TransformScaleMethod = ESpawnActorScaleMethod::MultiplyWithRoot;
		
		AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileTemplate, GetOwner()->GetTransform(),
																	  actorSpawnParameters);
		projectile->SetTargetDirection(UKismetMathLibrary::GetDirectionUnitVector(actorLocation, TopLeft));

		projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileTemplate, GetOwner()->GetTransform(),
														 actorSpawnParameters);
		projectile->SetTargetDirection(UKismetMathLibrary::GetDirectionUnitVector(actorLocation, TopRight));

		projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileTemplate, GetOwner()->GetTransform(),
														 actorSpawnParameters);
		projectile->SetTargetDirection(UKismetMathLibrary::GetDirectionUnitVector(actorLocation, BottomLeft));

		projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileTemplate, GetOwner()->GetTransform(),
														 actorSpawnParameters);
		projectile->SetTargetDirection(UKismetMathLibrary::GetDirectionUnitVector(actorLocation, BottomRight));
	}
}