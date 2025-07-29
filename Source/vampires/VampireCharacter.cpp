// Louis Hobbs | 2024-2025


#include "VampireCharacter.h"

#include "HealthComponent.h"
#include "WeaponInventoryComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AVampireCharacter::AVampireCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create Health Component
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	StaticMeshComponent->SetupAttachment(RootComponent);

	//Create Weapon Inventory Component
	WeaponInventoryComponent = CreateDefaultSubobject<UWeaponInventoryComponent>(TEXT("Weapon Inventory Component"));

	GetCharacterMovement()->SetPlaneConstraintNormal({0.0f, 0.0f, 1.0f});
}

// Called when the game starts or when spawned
void AVampireCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AVampireCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float NewYaw = FMath::Atan2(PreviousMovementDirection.Y, PreviousMovementDirection.X) * 180.0f / PI;
	FQuat NewRotation = FQuat::Slerp(StaticMeshComponent->GetComponentRotation().Quaternion(),
	                                 FRotator(0.0f, NewYaw, 0.0f).Quaternion(),
	                                 DeltaTime * SlerpSpeed);
	StaticMeshComponent->SetRelativeRotation(NewRotation);
}

void AVampireCharacter::Input_Move_Implementation(FVector2D Value)
{
	PreviousMovementDirection = Value;

	if (Value.Size() != 0.0f)
	{
		AddMovementInput({0.0f, 1.0f, 0.0f}, Value.Y);
		AddMovementInput({1.0f, 0.0f, 0.0f}, Value.X);
	}
}

UInputMappingContext* AVampireCharacter::Input_GetInputMappingContext_Implementation()
{
	return InputMappingContext;
}

FVector2D AVampireCharacter::Input_GetPreviousMovementDirection_Implementation()
{
	return PreviousMovementDirection;
}

UHealthComponent* AVampireCharacter::GetHealthComponent()
{
	return HealthComponent;
}
