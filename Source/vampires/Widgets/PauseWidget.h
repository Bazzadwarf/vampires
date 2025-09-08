// Louis Hobbs | 2024-2025

#pragma once

#include "CoreMinimal.h"
#include "VampireInteractiveWidget.h"
#include "Blueprint/UserWidget.h"
#include "PauseWidget.generated.h"

class UCustomButton;

/**
 * 
 */
UCLASS()
class VAMPIRES_API UPauseWidget : public UVampireInteractiveWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCustomButton> ResumeButton;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCustomButton> ReturnToMainMenuButton;

protected:
	virtual void NativeConstruct() override;

	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

private:
	UFUNCTION()
	void ResumeButtonOnClicked();
	
	UFUNCTION()
	void ResumeButtonOnFocused(FFocusEvent InFocusEvent);

	UFUNCTION()
	void ReturnToMainMenuButtonOnClicked();
	
	UFUNCTION()
	void ReturnToMainMenuButtonOnFocused(FFocusEvent InFocusEvent);
};
