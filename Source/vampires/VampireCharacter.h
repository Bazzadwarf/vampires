// Louis Hobbs | 2024-2025

#pragma once

#include "CoreMinimal.h"
#include "Inputable.h"
#include "GameFramework/Character.h"
#include "VampireCharacter.generated.h"

class UNiagaraSystem;
class AWeapon;
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
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	FVector2D PreviousMovementDirection = FVector2d(1.0f, 0.0f);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float SlerpSpeed = 10.0f;
	
protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UHealthComponent> HealthComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UWeaponInventoryComponent> WeaponInventoryComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USoundBase> OnDamagedSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USoundBase> OnDeathSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UNiagaraSystem> OnDamagedNiagaraSystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UNiagaraSystem> OnDeathNiagaraSystem;

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

	virtual FVector2D Input_GetPreviousMovementDirection_Implementation() override;

	UHealthComponent* GetHealthComponent();
};
