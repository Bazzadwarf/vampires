﻿// Louis Hobbs | 2024-2025

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Inputable.generated.h"

class UInputMappingContext;
// This class does not need to be modified.
UINTERFACE()
class UInputable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class VAMPIRES_API IInputable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Input_Move(FVector2D value);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Input_Pause();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	UInputMappingContext* Input_GetInputMappingContext();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	FVector2D Input_GetPreviousMovementDirection();
};
