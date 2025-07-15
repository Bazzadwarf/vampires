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
	int Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ExpRequiredForNextLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CumulativeExpForNextLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CumulativeExpForPreviousLevel;
};
