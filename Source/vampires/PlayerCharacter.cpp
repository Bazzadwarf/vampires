// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "VampirePlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EXPComponent.h"
#include "GoldComponent.h"
#include "InputMappingContext.h"
#include "WeaponInventoryComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/SpringArmComponent.h"

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
