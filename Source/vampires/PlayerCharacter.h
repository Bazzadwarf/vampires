// Louis Hobbs | 2024-2025

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

	UPROPERTY(EditAnywhere)
	UWidgetComponent* HealthBarWidgetComponent;

	APlayerCharacter();

protected:
	virtual void BeginPlay() override;

public:

	UEXPComponent* GetEXPComponent();

	UGoldComponent* GetGoldComponent();
};
