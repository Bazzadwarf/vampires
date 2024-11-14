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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSoftObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UInputAction* MovementAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UEXPComponent* EXPComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UGoldComponent* GoldComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWeaponInventoryComponent* WeaponInventoryComponent;

	FVector2D PreviousMovementDirection = FVector2d(1.0f, 0.0f);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UUserWidget> PlayerHUD = nullptr;

	UPROPERTY(EditAnywhere)
	UWidgetComponent* HealthBarWidgetComponent;

private:
	FTimerHandle GarlicTimerHandle;

	UUserWidget* currentPlayerHUD = nullptr;

public:
	APlayerCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UEXPComponent* GetEXPComponent();

	UGoldComponent* GetGoldComponent();

private:
	UFUNCTION()
	void MovementCallback(const FInputActionInstance& Instance);
};
