// Louis Hobbs | 2024-2025

#pragma once

#include "CoreMinimal.h"
#include "ExpTableRow.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FExpTableRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Level = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ExpRequiredForNextLevel = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CumulativeExpForNextLevel = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CumulativeExpForPreviousLevel = 0;
};
