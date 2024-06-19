// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h"

#include "PlayerCharacter.h"

// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	// Create Sphere Component
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	SphereComponent->SetupAttachment(RootComponent);
	SphereComponent->SetSphereRadius(25.0f);
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &APickup::OnBeginOverlap);
}

void APickup::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// TODO: Move actor towards player when in range
}

void APickup::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                             UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor))
	{
		// TODO: Add extra functionality
		Destroy();
	}
}

