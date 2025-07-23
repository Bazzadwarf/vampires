// Louis Hobbs | 2024-2025


#include "Pickup.h"

#include "ObjectPoolManager.h"
#include "PlayerCharacter.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PickupDataAsset.h"
#include "GameFramework/GameModeBase.h"
#include "Interfaces/Pools.h"
#include "NiagaraComponent.h"

// Sets default values
APickup::APickup()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create Sphere Component
	InnerSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Inner Sphere Component"));
	SetRootComponent(InnerSphereComponent);
	InnerSphereComponent->SetSphereRadius(25.0f);
	InnerSphereComponent->SetCollisionProfileName(TEXT("Pickup"));

	OuterSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Outer Sphere Component"));
	OuterSphereComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	OuterSphereComponent->SetSphereRadius(250.0f);
	OuterSphereComponent->SetCollisionProfileName(TEXT("Pickup"));

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	StaticMeshComponent->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
	StaticMeshComponent->SetRelativeScale3D(FVector(.5f, .5f, .5f));
	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	StaticMeshComponent->SetupAttachment(RootComponent);

	TimelineComponent = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline Component"));
	TimelineComponent->SetDirectionPropertyName(FName("TimelineDirection"));
	TimelineComponent->SetLooping(false);
	TimelineComponent->SetTimelineLength(5.0f);
	TimelineComponent->SetTimelineLengthMode(TL_TimelineLength);
	TimelineComponent->SetPlaybackPosition(0.0f, false);

	onTimelineCallback.BindUFunction(this, FName(TEXT("TimelineCallback")));
	onTimelineFinishedCallback.BindUFunction(this, FName(TEXT("TimelineFinishedCallback")));

	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara Component"));
	NiagaraComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	NiagaraComponent->DeactivateImmediate();
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

void APickup::LoadDataFromDataAsset_Implementation(UPickupDataAsset* PickupDataAsset, FVector Location)
{
	if (PickupDataAsset != nullptr)
	{
		PickupValue = PickupDataAsset->PickupValue;
		StaticMeshComponent->SetStaticMesh(PickupDataAsset->PickupStaticMesh);
		PickupSoundBase = PickupDataAsset->PickupSoundBase;
		CurveFloat = PickupDataAsset->CurveFloat;
		PickupLocation = Location;
		
		if (CurveFloat != nullptr)
		{
			TimelineComponent->AddInterpFloat(CurveFloat, onTimelineCallback);
			TimelineComponent->SetTimelineFinishedFunc(onTimelineFinishedCallback);
		}
	}
}

void APickup::ResetData_Implementation()
{
	PickupValue = 0;
	StaticMeshComponent->SetStaticMesh(nullptr);
	PickupSoundBase = nullptr;
	CurveFloat = nullptr;

	TSet<UCurveBase*> AllCurves;
	TimelineComponent->GetAllCurves(AllCurves);
	if (AllCurves.Num() > 0)
	{
		AllCurves.Reset();
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

		AGameModeBase* gamemode = UGameplayStatics::GetGameMode(GetWorld());
		if (UKismetSystemLibrary::DoesImplementInterface(gamemode, UPools::StaticClass()))
		{
			if (AObjectPoolManager* objectPoolManager = IPools::Execute_GetProjectileObjectPoolManager(gamemode))
			{
				TimelineComponent->Stop();
				ResetData_Implementation();
				objectPoolManager->ReturnObject(this);
			}
		}
		else
		{
			Destroy();
		}
	}
}

void APickup::OnOuterBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                  const FHitResult& SweepResult)
{
	if (!TimelineComponent->IsPlaying() && UGameplayStatics::GetPlayerCharacter(GetWorld(), 0) == Cast<ACharacter>(OtherActor))
	{
		PlayTimeLine();
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
	TimelineComponent->PlayFromStart();
}
