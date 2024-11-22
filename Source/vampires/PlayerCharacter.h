// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VampireCharacter.h"
#include "PlayerCharacter.generated.h"

struct FInputActionInstance;
class UWidgetComponent;
class UWeaponInventoryComponent;
class UGoldComponent;
class UEXPComponent;
class UCameraComponent;
class USpringArmComponent;
class UInputMappingContext;
class UInputAction;

/**
 * 
 */
UCLASS()
class VAMPIRES_API APlayerCharacter : public AVampireCharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USpringArmComponent* CameraSpringArmComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* CameraComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UEXPComponent* EXPComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UGoldComponent* GoldComponent;

	FVector2D PreviousMovementDirection = FVector2d(1.0f, 0.0f);

	UPROPERTY(EditAnywhere)
	UWidgetComponent* HealthBarWidgetComponent;

	APlayerCharacter();

protected:
	virtual void BeginPlay() override;

public:

	UEXPComponent* GetEXPComponent();

	UGoldComponent* GetGoldComponent();
};
