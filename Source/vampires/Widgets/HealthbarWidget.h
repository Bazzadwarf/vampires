// Louis Hobbs | 2024-2025

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthbarWidget.generated.h"

struct FDamageInfo;
class UProgressBar;
/**
 * 
 */
UCLASS()
class VAMPIRES_API UHealthbarWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UProgressBar> HealthBar;

	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void UpdateHealthBar(FDamageInfo DamageInfo);
};
