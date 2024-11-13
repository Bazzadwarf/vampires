// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Weapons/ProjectileWeapon.h"

// Sets default values
AProjectile::AProjectile()
{	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	SetRootComponent(SphereComponent);
	SphereComponent->SetSphereRadius(50.0f);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement->ProjectileGravityScale = 0.0f;
	ProjectileMovement->Friction = 0.0f;;
	ProjectileMovement->bIsSliding = true;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	AProjectileWeapon* OwnerWeapon = Cast<AProjectileWeapon>(GetOwner()); 
	SphereComponent->OnComponentBeginOverlap.AddDynamic(OwnerWeapon, &AProjectileWeapon::OnProjectileBeginOverlap);

	ProjectileMovement->InitialSpeed = ProjectileSpeed;
	ProjectileMovement->MaxSpeed = ProjectileSpeed;
}

void AProjectile::SetTargetDirection(FVector direction)
{
	TargetDirection = direction;
	ProjectileMovement->SetVelocityInLocalSpace(TargetDirection * ProjectileSpeed);
}

