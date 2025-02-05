// Louis Hobbs | 2024-2025


#include "Pickup.h"
#include "PlayerCharacter.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PaperSpriteComponent.h"

// Sets default values
APickup::APickup()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create Sphere Component
	InnerSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Inner Sphere Component"));
	SetRootComponent(InnerSphereComponent);
	InnerSphereComponent->SetSphereRadius(25.0f);

	OuterSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Outer Sphere Component"));
	OuterSphereComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	OuterSphereComponent->SetSphereRadius(250.0f);

	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite Component"));
	SpriteComponent->SetRelativeRotation(FRotator(0.0f, 90.0f, -90.0f));
	SpriteComponent->SetRelativeScale3D(FVector(.5f, .5f, .5f));
	SpriteComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SpriteComponent->SetupAttachment(RootComponent);

	TimelineComponent = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline Component"));
	TimelineComponent->SetDirectionPropertyName(FName("TimelineDirection"));
	TimelineComponent->SetLooping(false);
	TimelineComponent->SetTimelineLength(5.0f);
	TimelineComponent->SetTimelineLengthMode(TL_TimelineLength);
	TimelineComponent->SetPlaybackPosition(0.0f, false);

	onTimelineCallback.BindUFunction(this, FName(TEXT("TimelineCallback")));
	onTimelineFinishedCallback.BindUFunction(this, FName(TEXT("TimelineFinishedCallback")));
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();

	InnerSphereComponent->OnComponentBeginOverlap.AddDynamic(this, &APickup::OnInnerBeginOverlap);
	OuterSphereComponent->OnComponentBeginOverlap.AddDynamic(this, &APickup::OnOuterBeginOverlap);

	if (CurveFloat != nullptr)
	{
		TimelineComponent->AddInterpFloat(CurveFloat, onTimelineCallback);
		TimelineComponent->SetTimelineFinishedFunc(onTimelineFinishedCallback);
	}
}

void APickup::OnInnerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
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

void APickup::OnOuterBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                  const FHitResult& SweepResult)
{
	if (APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor))
	{
		PickupLocation = GetActorLocation();
		PlayTimeLine();

		double dist = FVector::Distance(GetActorLocation(), PlayerCharacter->GetActorLocation());

		if (dist < OuterSphereComponent->GetScaledSphereRadius())
		{
			double ratio = FMath::Abs((dist / OuterSphereComponent->GetScaledSphereRadius()) - 1.0f);
			TimelineComponent->SetNewTime(ratio);
		}
	}
}

void APickup::TimelineCallback(float val)
{
	FVector actorLocation = PickupLocation;
	FVector playerLocation = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation();
	FVector location = FMath::Lerp(actorLocation, playerLocation, val);
	SetActorLocation(location);
}

void APickup::TimelineFinishedCallback()
{
}

void APickup::PlayTimeLine()
{
	TimelineComponent->Play();
}
