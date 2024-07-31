// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "EnemyCharacter.h"
#include "Weapons/MagicWandWeapon.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	SphereComponent->SetupAttachment(RootComponent);
	SphereComponent->SetSphereRadius(50.0f);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	AMagicWandWeapon* OwnerWeapon = Cast<AMagicWandWeapon>(GetOwner()); 
	SphereComponent->OnComponentBeginOverlap.AddDynamic(OwnerWeapon, &AMagicWandWeapon::OnProjectileBeginOverlap);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetActorLocation(GetActorLocation() + (TargetDirection * ProjectileSpeed));
}

