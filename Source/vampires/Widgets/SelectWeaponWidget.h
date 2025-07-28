// Louis Hobbs | 2024-2025

#pragma once

#include "CoreMinimal.h"
#include "VampireInteractiveWidget.h"
#include "SelectWeaponWidget.generated.h"


class AWeapon;
class UListView;
class UButton;
/**
 * 
 */
UCLASS()
class VAMPIRES_API USelectWeaponWidget : public UVampireInteractiveWidget
{
	GENERATED_BODY()
protected:

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UButton> BackButton;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UTextBlock> BackTextBlock;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UListView> UpgradesListView;
	
	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<AWeapon>> StarterWeapons;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> PreviousWidget;

	virtual void NativeConstruct() override;
	
private:
	
	UFUNCTION()
	void BackButtonClicked();

	UFUNCTION()
	void BackButtonTextBlockHoveredDelegate() { SetTextBlockHovered(BackTextBlock); }

	UFUNCTION()
	void BackButtonTextBlockUnhoveredDelegate() { SetTextBlockUnhovered(BackTextBlock); }
};
