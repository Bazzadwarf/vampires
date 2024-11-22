// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inputable.h"
#include "GameFramework/Character.h"
#include "VampireCharacter.generated.h"

class UWeaponInventoryComponent;
class UInputAction;
class UHealthComponent;
class UPaperFlipbookComponent;

UCLASS(Abstract)
class VAMPIRES_API AVampireCharacter : public ACharacter, public IInputable
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UPaperFlipbookComponent* PaperFlipbookComponent;

protected:
	UPROPERTY()
	UHealthComponent* HealthComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UInputMappingContext> InputMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWeaponInventoryComponent* WeaponInventoryComponent;

public:
	// Sets default values for this character's properties
	AVampireCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Input_Move_Implementation(FVector2D value) override;

	virtual UInputMappingContext* Input_GetInputMappingContext_Implementation() override;

	UHealthComponent* GetHealthComponent();
};
