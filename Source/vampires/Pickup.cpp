// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h"

#include "PlayerCharacter.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PaperSpriteComponent.h"

// Sets default values
APickup::APickup()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create Sphere Component
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	SetRootComponent(SphereComponent);
	SphereComponent->SetSphereRadius(25.0f);

	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite Component"));
	SpriteComponent->SetRelativeRotation(FRotator(0.0f, 90.0f, -90.0f));
	SpriteComponent->SetRelativeScale3D(FVector(.5f, .5f, .5f));
	SpriteComponent->SetupAttachment(RootComponent);
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
	FVector actorLocation = GetActorLocation();
	FVector playerLocation = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation();
	double currentDistance = FVector::Distance(actorLocation, playerLocation);

	if (currentDistance <= PickupMovementRange)
	{
		double speed = 400 / currentDistance;
		FVector location = FMath::VInterpTo(actorLocation, playerLocation, DeltaSeconds, speed);
		SetActorLocation(location);
	}
}

void APickup::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                             UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                             const FHitResult& SweepResult)
{
	if (APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor))
	{
		// TODO: Add extra functionality
		if (PickupSoundBase)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), PickupSoundBase);
		}

		Destroy();
	}
}
