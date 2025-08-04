// Louis Hobbs | 2024-2025

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverWidget.generated.h"

class UTextBlock;
class UButton;
/**
 * 
 */
UCLASS()
class VAMPIRES_API UGameOverWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UButton> ReturnButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr <UTextBlock> LevelBlock;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr <UTextBlock> TimerBlock;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr <UTextBlock> KillBlock;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr <UTextBlock> GoldBlock;

	virtual void NativeConstruct() override;

public:
	void SetGameInfo(int Level, float Timer, int Kill, int Gold);
	
private:
	UFUNCTION()
	void ReturnButtonClicked();
};
