// Louis Hobbs | 2024-2025

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Playerable.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable)
class UPlayerable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class VAMPIRES_API IPlayerable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void UpdateTimerHUDElement(float deltaTime);
};
