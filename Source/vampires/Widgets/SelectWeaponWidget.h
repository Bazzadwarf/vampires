// Louis Hobbs | 2024-2025

#pragma once

#include "CoreMinimal.h"
#include "VampireInteractiveWidget.h"
#include "SelectWeaponWidget.generated.h"


class UStarterWeaponButtonWidget;
class UScrollBox;
class UCustomListView;
class AWeapon;
class UListView;
class UCustomButton;
/**
 * 
 */
UCLASS()
class VAMPIRES_API USelectWeaponWidget : public UVampireInteractiveWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCustomButton> BackButton;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UScrollBox> StarterWeaponsScrollBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UStarterWeaponButtonWidget> StarterWeaponButtonWidgetTemplate;

protected:
	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<AWeapon>> StarterWeapons;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> PreviousWidget;

	FTimerHandle TimerHandle;

	virtual void NativeConstruct() override;

	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

private:
	UFUNCTION()
	void BackButtonClicked();

	UFUNCTION()
	void BackButtonFocused(FFocusEvent InFocusEvent);

	TArray<TObjectPtr<UStarterWeaponButtonWidget>> Buttons;
};
