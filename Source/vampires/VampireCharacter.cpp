// Fill out your copyright notice in the Description page of Project Settings.


#include "VampireCharacter.h"

#include "HealthComponent.h"
#include "PaperFlipbookComponent.h"

// Sets default values
AVampireCharacter::AVampireCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create Health Component
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));

	PaperFlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Paper Flipbook Component"));
	PaperFlipbookComponent->SetRelativeRotation(FRotator(0.0f, 90.0f,-90.0f));
	PaperFlipbookComponent->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));
	PaperFlipbookComponent->SetupAttachment(RootComponent);
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

}

void AVampireCharacter::Input_Move_Implementation(FVector2D value)
{
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

UHealthComponent* AVampireCharacter::GetHealthComponent()
{
	return HealthComponent;
}

