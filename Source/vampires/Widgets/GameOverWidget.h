// Louis Hobbs | 2024-2025

#pragma once

#include "CoreMinimal.h"
#include "VampireInteractiveWidget.h"
#include "GameOverWidget.generated.h"

class UCustomButton;
class UTextBlock;
/**
 * 
 */
UCLASS()
class VAMPIRES_API UGameOverWidget : public UVampireInteractiveWidget
{
	GENERATED_BODY()

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCustomButton> ReturnButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> LevelBlock;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TimerBlock;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> KillBlock;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> GoldBlock;

	virtual void NativeConstruct() override;

	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

public:
	void SetGameInfo(int Level, float Timer, int Kill, int Gold);

private:
	UFUNCTION()
	void ReturnButtonOnClicked();

	UFUNCTION()
	void ReturnButtonOnFocused(FFocusEvent InFocusEvent);
};
