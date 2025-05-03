// Louis Hobbs | 2024-2025

#pragma once

#include "CoreMinimal.h"
#include "VampireCharacter.h"
#include "Components/TimelineComponent.h"
#include "PlayerCharacter.generated.h"

struct FDamageInfo;
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
	TObjectPtr<UEXPComponent> EXPComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UGoldComponent> GoldComponent;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UWidgetComponent> HealthBarWidgetComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UTimelineComponent> CameraShakeTimelineComponent = nullptr;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UCurveFloat> CameraShakeCurve;

	UPROPERTY(EditAnywhere)
	float CameraShakeStrength = 100.0f;

private:
	
	TObjectPtr<APlayerCameraManager> PlayerCameraManager = nullptr;
	
	APlayerCharacter();

private:
	FOnTimelineFloat onTimelineCallback;
	FOnTimelineEventStatic onTimelineFinishedCallback;

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

	UFUNCTION()
	void CameraShakeTimelineCallback(float val);

	UFUNCTION()
	void CameraShakeTimelineFinishedCallback();
};
