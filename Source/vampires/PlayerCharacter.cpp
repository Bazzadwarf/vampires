// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "VampirePlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Kismet/GameplayStatics.h"

APlayerCharacter::APlayerCharacter()
{
	// Create Camera Boom
	CameraSpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArmComponent"));
	CameraSpringArmComponent->SetupAttachment(RootComponent);
	CameraSpringArmComponent->bDoCollisionTest = true;
	CameraSpringArmComponent->bUsePawnControlRotation = false;
	CameraSpringArmComponent->TargetArmLength = 1000;
	CameraSpringArmComponent->bEnableCameraLag = false;
	CameraSpringArmComponent->SocketOffset = {0.0f, 0.0f, 0.0f};
	CameraSpringArmComponent->SetRelativeRotation({-90.0, 0.0f, 0.0f});

	// Create Camera
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	CameraComponent->SetupAttachment(CameraSpringArmComponent, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;
	CameraComponent->SetProjectionMode(ECameraProjectionMode::Type::Orthographic);
	CameraComponent->SetOrthoWidth(4000.0f);

	// Create EXP Component
	EXPComponent = CreateDefaultSubobject<UEXPComponent>(TEXT("EXP Component"));

	// Create Gold Component
	GoldComponent = CreateDefaultSubobject<UGoldComponent>(TEXT("Gold Component"));

	// Create Garlic Sphere Component
	GarlicSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Garlic Sphere Component"));
	GarlicSphereComponent->SetupAttachment(RootComponent);
	GarlicSphereComponent->SetSphereRadius(150.0f);

	//Create Weapon Inventory Component
	WeaponInventoryComponent = CreateDefaultSubobject<UWeaponInventoryComponent>(TEXT("Weapon Inventory Component"));
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	GarlicSphereComponent->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnGarlicBeginOverlap);
	GarlicSphereComponent->OnComponentEndOverlap.AddDynamic(this, &APlayerCharacter::OnGarlicEndOverlap);
	GetWorldTimerManager().SetTimer(GarlicTimerHandle, this, &APlayerCharacter::GarlicUpdate, GarlicUpdateTime, true);
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (AVampirePlayerController* TankPlayerController = Cast<AVampirePlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(TankPlayerController->GetLocalPlayer()))
		{
			if (!InputMappingContext.IsNull())
			{
				InputSystem->AddMappingContext(InputMappingContext.LoadSynchronous(), 0);
			}
		}
	}

	if (UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (MovementAction)
		{
			Input->BindAction(MovementAction, ETriggerEvent::Triggered, this, &APlayerCharacter::MovementCallback);
		}
	}
}

UEXPComponent* APlayerCharacter::GetEXPComponent()
{
	return EXPComponent;
}

UGoldComponent* APlayerCharacter::GetGoldComponent()
{
	return GoldComponent;
}

void APlayerCharacter::MovementCallback(const FInputActionInstance& Instance)
{
	FVector2D vec2 = Instance.GetValue().Get<FVector2D>();

	if (vec2.Size() != 0.0f)
	{
		AddMovementInput({0.0f, 1.0f, 0.0f}, vec2.Y);
		AddMovementInput({1.0f, 0.0f, 0.0f}, vec2.X);
	}
}

void APlayerCharacter::OnGarlicBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                            const FHitResult& SweepResult)
{
	if (AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(OtherActor))
	{
		OverlappedEnemies.Add(Enemy);
	}
}

void APlayerCharacter::OnGarlicEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                          UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(OtherActor))
	{
		OverlappedEnemies.Remove(Enemy);
	}
}

void APlayerCharacter::GarlicUpdate()
{
	TArray<AEnemyCharacter*> OverlappedEnemiesCache = OverlappedEnemies;

	for (int i = 0; i < OverlappedEnemiesCache.Num(); i++)
	{
		bool deadCheck = false;
		UHealthComponent* EnemyHealthComponent = OverlappedEnemiesCache[i]->GetHealthComponent();

		if (!EnemyHealthComponent->GetIsDead())
		{
			FVector Direction = OverlappedEnemiesCache[i]->GetActorLocation() - this->GetActorLocation();
			Direction.Normalize();
			float distance = GarlicSphereComponent->GetScaledSphereRadius();
			Direction *= distance;
			OverlappedEnemiesCache[i]->SetActorLocation(OverlappedEnemiesCache[i]->GetActorLocation() + Direction);
			
			if (EnemyHealthComponent->GetCurrentHealth() < GarlicDamage)
			{
				deadCheck = true;
			}
			
			EnemyHealthComponent->TakeDamage(OverlappedEnemiesCache[i], GarlicDamage, nullptr, GetController(), this);
		}

		if (deadCheck)
		{
			i -= 1;
		}
	}	
}
