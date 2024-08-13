// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "VampirePlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

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

	//Create Weapon Inventory Component
	WeaponInventoryComponent = CreateDefaultSubobject<UWeaponInventoryComponent>(TEXT("Weapon Inventory Component"));
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (PlayerHUD)
	{
		currentPlayerHUD = UUserWidget::CreateWidgetInstance(*GetWorld(), PlayerHUD, FName("Player HUD"));

		if (currentPlayerHUD)
		{
			currentPlayerHUD->AddToViewport();
		}
	}
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
	PreviousMovementDirection = Instance.GetValue().Get<FVector2D>();

	if (PreviousMovementDirection.Size() != 0.0f)
	{
		AddMovementInput({0.0f, 1.0f, 0.0f}, PreviousMovementDirection.Y);
		AddMovementInput({1.0f, 0.0f, 0.0f}, PreviousMovementDirection.X);
	}
}
