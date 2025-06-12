// Louis Hobbs | 2024-2025

#pragma once

#include "CoreMinimal.h"
#include "VampireInteractiveWidget.h"
#include "SelectWeaponWidget.generated.h"


class UListView;
class UButton;
/**
 * 
 */
UCLASS()
class VAMPIRES_API USelectWeaponWidget : public UVampireInteractiveWidget
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UButton* BackButton;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UListView* UpgradesListView;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> PreviousWidget;

	virtual void NativeConstruct() override;
	
private:
	
	UFUNCTION()
	void BackButtonClicked();

};
