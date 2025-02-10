// Louis Hobbs | 2024-2025


#include "VampireCharacter.h"

#include "HealthComponent.h"
#include "PaperFlipbookComponent.h"
#include "WeaponInventoryComponent.h"

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

	float newYaw = FMath::Atan2(PreviousMovementDirection.Y, PreviousMovementDirection.X) * 180.0f / PI;
	FQuat newRotation = FQuat::Slerp(StaticMeshComponent->GetComponentRotation().Quaternion(),
	                                 FRotator(0.0f, newYaw, 0.0f).Quaternion(),
	                                 DeltaTime * SlerpSpeed);
	StaticMeshComponent->SetRelativeRotation(newRotation);
}

void AVampireCharacter::Input_Move_Implementation(FVector2D value)
{
	PreviousMovementDirection = value;
	
	if (value.Size() != 0.0f)
	{
		AddMovementInput({0.0f, 1.0f, 0.0f}, value.Y);
		AddMovementInput({1.0f, 0.0f, 0.0f}, value.X);
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

