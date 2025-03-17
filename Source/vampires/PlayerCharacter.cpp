// Louis Hobbs | 2024-2025


#include "PlayerCharacter.h"

#include "VampirePlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EXPComponent.h"
#include "GoldComponent.h"
#include "InputMappingContext.h"
#include "WeaponInventoryComponent.h"
#include "Components/WidgetComponent.h"

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
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

UEXPComponent* APlayerCharacter::GetEXPComponent()
{
	return EXPComponent;
}

UGoldComponent* APlayerCharacter::GetGoldComponent()
{
	return GoldComponent;
}
