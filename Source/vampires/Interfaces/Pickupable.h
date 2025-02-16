// Louis Hobbs | 2024-2025

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Pickupable.generated.h"

class UPickupDataAsset;
// This class does not need to be modified.
UINTERFACE()
class UPickupable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class VAMPIRES_API IPickupable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent)
	void LoadDataFromDataAsset(UPickupDataAsset* PickupDataAsset);

	UFUNCTION(BlueprintNativeEvent)
	void ResetData();
};
