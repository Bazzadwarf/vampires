// Louis Hobbs | 2024-2025

#pragma once

#include "CoreMinimal.h"
#include "VampireCharacter.h"
#include "Components/TimelineComponent.h"
#include "UnrealClient.h"
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

protected:
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
	UPROPERTY()
	TObjectPtr<APlayerCameraManager> PlayerCameraManager = nullptr;

	FOnTimelineFloat OnTimelineCallback;
	FOnTimelineEventStatic OnTimelineFinishedCallback;

	FTimerHandle ResizeViewportTimerDelegate;
	FVector TopLeft, TopLeftDir, BottomRight, BottomRightDir;
	
	APlayerCharacter();

protected:
	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;

	UEXPComponent* GetEXPComponent();

	UGoldComponent* GetGoldComponent();

private:
	UFUNCTION()
	virtual void OnDamaged(FDamageInfo DamageInfo);

	UFUNCTION()
	virtual void OnDeath(FDamageInfo DamageInfo);

	UFUNCTION()
	void CameraShakeTimelineCallback(float Val);

	UFUNCTION()
	void CameraShakeTimelineFinishedCallback();

	UFUNCTION()
	void ResizeViewportTimerCallback();
	
	void OnViewportResized(FViewport* ViewPort, uint32 val);
};
