// Louis Hobbs | 2024-2025


#include "PlayerCharacter.h"

#include "VampirePlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EXPComponent.h"
#include "GoldComponent.h"
#include "HealthComponent.h"
#include "InputMappingContext.h"
#include "WeaponInventoryComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"

APlayerCharacter::APlayerCharacter()
{
	// Create EXP Component
	EXPComponent = CreateDefaultSubobject<UEXPComponent>(TEXT("EXP Component"));

	// Create Gold Component
	GoldComponent = CreateDefaultSubobject<UGoldComponent>(TEXT("Gold Component"));

	// Create HealthBar Widget Component
	HealthBarWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Healthbar"));
	HealthBarWidgetComponent->SetupAttachment(RootComponent);
	HealthBarWidgetComponent->SetRelativeLocation(FVector(0, 0, 90));
	HealthBarWidgetComponent->SetTwoSided(true);
	HealthBarWidgetComponent->SetBackgroundColor(FLinearColor(1, 1, 1, 0));
	HealthBarWidgetComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	CameraShakeTimelineComponent = CreateDefaultSubobject<UTimelineComponent>(TEXT("Camera Shake Timeline Component"));
	CameraShakeTimelineComponent->SetDirectionPropertyName(FName("TimelineDirection"));
	CameraShakeTimelineComponent->SetLooping(false);
	CameraShakeTimelineComponent->SetTimelineLength(0.5f);
	CameraShakeTimelineComponent->SetTimelineLengthMode(TL_TimelineLength);
	CameraShakeTimelineComponent->SetPlaybackPosition(0.0f, false);

	onTimelineCallback.BindUFunction(this, FName(TEXT("CameraShakeTimelineCallback")));
	onTimelineFinishedCallback.BindUFunction(this, FName(TEXT("CameraShakeTimelineFinishedCallback")));
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetHealthComponent()->OnDamaged.AddDynamic(this, &APlayerCharacter::OnDamaged);
	GetHealthComponent()->OnDeath.AddDynamic(this, &APlayerCharacter::OnDeath);

	if (CameraShakeCurve != nullptr)
	{
		CameraShakeTimelineComponent->AddInterpFloat(CameraShakeCurve, onTimelineCallback);
		CameraShakeTimelineComponent->SetTimelineFinishedFunc(onTimelineFinishedCallback);
	}

	PlayerCameraManager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	
	FVector TopLeft, TopLeftDir;
	FVector BottomRight, BottomRightDir;

	FVector2d ViewportSize;
	GEngine->GameViewport->GetViewportSize(ViewportSize);

	PlayerController->DeprojectScreenPositionToWorld(0, 0, TopLeft, TopLeftDir);
	PlayerController->DeprojectScreenPositionToWorld(ViewportSize.X, ViewportSize.Y, BottomRight, BottomRightDir);

	auto location = GetActorLocation();
	location.X = FMath::Clamp(location.X, BottomRight.X, TopLeft.X);
	location.Y = FMath::Clamp(location.Y, TopLeft.Y, BottomRight.Y);

	SetActorLocation(location);
}

UEXPComponent* APlayerCharacter::GetEXPComponent()
{
	return EXPComponent;
}

UGoldComponent* APlayerCharacter::GetGoldComponent()
{
	return GoldComponent;
}

void APlayerCharacter::OnDamaged(FDamageInfo damageInfo)
{
	if (OnDamagedSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), OnDamagedSound, GetActorLocation());
	}

	CameraShakeTimelineComponent->PlayFromStart();
}

void APlayerCharacter::OnDeath(FDamageInfo damageInfo)
{
	if (OnDeathSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), OnDeathSound, GetActorLocation());
	}

	// TODO: End the game
}

void APlayerCharacter::CameraShakeTimelineCallback(float val)
{
	auto PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	auto cameraActor = PlayerController->GetViewTarget();
	cameraActor->SetActorLocation(FVector(FMath::RandRange(0.0f, CameraShakeStrength) * val, FMath::RandRange(0.0f, CameraShakeStrength) * val, 0.0f));
}

void APlayerCharacter::CameraShakeTimelineFinishedCallback()
{
	auto PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	auto cameraActor = PlayerController->GetViewTarget();
	cameraActor->SetActorLocation(FVector::ZeroVector);
}
