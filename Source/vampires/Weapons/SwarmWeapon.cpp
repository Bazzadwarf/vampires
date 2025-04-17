// Louis Hobbs | 2024-2025


#include "SwarmWeapon.h"

#include "VectorTypes.h"
#include "Kismet/KismetSystemLibrary.h"
#include "vampires/EnemyCharacter.h"


// Sets default values
ASwarmWeapon::ASwarmWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TimelineComponent = CreateDefaultSubobject<UTimelineComponent>("TimelineComponent");
	TimelineComponent->SetDirectionPropertyName(FName("TimelineDirection"));
	TimelineComponent->SetLooping(true);
	TimelineComponent->SetTimelineLength(1.0f);
	TimelineComponent->SetTimelineLengthMode(TL_TimelineLength);
	TimelineComponent->SetPlaybackPosition(0.0f, false);

	onTimelineCallback.BindUFunction(this, FName(TEXT("TimelineCallback")));
}

// Called when the game starts or when spawned
void ASwarmWeapon::BeginPlay()
{
	Super::BeginPlay();

	// Spawn the swarm actors in
	SwarmActors.Add(GetWorld()->SpawnActor<AActor>(SwarmActor));
	SwarmActors.Add(GetWorld()->SpawnActor<AActor>(SwarmActor));

	// Start the timeline
	if (SwarmCurve != nullptr)
	{
		TimelineComponent->AddInterpFloat(SwarmCurve, onTimelineCallback);
	}

	TimelineComponent->SetPlayRate(TimelinePlayRate);
	TimelineComponent->PlayFromStart();
	
}

void ASwarmWeapon::TimelineCallback(float val)
{
	float num = SwarmActors.Num();

	for (int i = 0; i < num; i++)
	{
		float actorIndex = (i + 1);
		float offset = (actorIndex / num) * 360.0f;
		FVector CenterLocation = GetActorLocation();
		FVector Direction = FVector(0.0, 1, 0.0);
		FVector RotatedDirection = Direction.RotateAngleAxis(val * 360.0f + offset, FVector(0.0f, 0.0f, 1.0f));
		FVector NewLocation = CenterLocation + (RotatedDirection * Distance);
		SwarmActors[i]->SetActorLocation(NewLocation);
	}
}

bool ASwarmWeapon::UpgradeWeapon_Implementation()
{
	if (!Super::UpgradeWeapon_Implementation()) return false;

	switch (CurrentLevel)
	{
	case 1:
		SwarmActors.Add(GetWorld()->SpawnActor<AActor>(SwarmActor));
		break;
	case 2:
		Distance *= 1.25f;
		TimelineComponent->SetPlayRate(TimelineComponent->GetPlayRate() * 1.3f); 
		break;
	case 3:
		Damage += 10;
		break;
	case 4:
		SwarmActors.Add(GetWorld()->SpawnActor<AActor>(SwarmActor));
		break;
	case 5:
		Distance *= 1.25f;
		TimelineComponent->SetPlayRate(TimelineComponent->GetPlayRate() * 1.3f); 
		break;
	case 6:
		Damage += 10;
		break;
	case 7:
		SwarmActors.Add(GetWorld()->SpawnActor<AActor>(SwarmActor));
		break;
	default:
		return false;
	}

	ResetWeaponTimer();
	return true;
}

