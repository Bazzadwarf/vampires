// Louis Hobbs | 2024-2025

#pragma once

#include "CoreMinimal.h"
#include "VampireInteractiveWidget.h"
#include "Blueprint/UserWidget.h"
#include "GameOverWidget.generated.h"

class UTextBlock;
class UButton;
/**
 * 
 */
UCLASS()
class VAMPIRES_API UGameOverWidget : public UVampireInteractiveWidget
{
	GENERATED_BODY()

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> ReturnButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ReturnBlock;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> LevelBlock;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TimerBlock;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> KillBlock;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> GoldBlock;

	virtual void NativeConstruct() override;

public:
	void SetGameInfo(int Level, float Timer, int Kill, int Gold);

private:
	UFUNCTION()
	void ReturnButtonOnClicked();

	UFUNCTION()
	void ReturnButtonOnHovered();

	UFUNCTION()
	void ReturnButtonOnUnhovered();
};
