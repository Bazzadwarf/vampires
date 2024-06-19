// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyCharacter.h"
#include "EXPComponent.h"
#include "GoldComponent.h"
#include "VampireCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PlayerCharacter.generated.h"

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float GarlicDamage = 51.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float GarlicUpdateTime = 1.0f;

protected:
	UPROPERTY()
	UEXPComponent* EXPComponent;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* GarlicSphereComponent;

	UPROPERTY()
	TArray<AEnemyCharacter*> OverlappedEnemies;

	UPROPERTY()
	UGoldComponent* GoldComponent;

private:
	FTimerHandle GarlicTimerHandle;

public:
	APlayerCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

private:
	UFUNCTION()
	void MovementCallback(const FInputActionInstance& Instance);

	UFUNCTION()
	void OnGarlicBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                          UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                          const FHitResult& SweepResult);

	UFUNCTION()
	void OnGarlicEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                        int32 OtherBodyIndex);

	UFUNCTION()
	void GarlicUpdate();
};
