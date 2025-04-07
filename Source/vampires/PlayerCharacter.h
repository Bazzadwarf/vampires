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
	UEXPComponent* EXPComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UGoldComponent* GoldComponent;

	UPROPERTY(EditAnywhere)
	UWidgetComponent* HealthBarWidgetComponent;

	APlayerCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UEXPComponent* GetEXPComponent();

	UGoldComponent* GetGoldComponent();

private:
	UFUNCTION()
	virtual void OnDamaged(FDamageInfo damageInfo);

	UFUNCTION()
	virtual void OnDeath(FDamageInfo damageInfo);
};
