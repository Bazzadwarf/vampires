// Louis Hobbs | 2024-2025

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "StarterWeaponButtonDataObject.generated.h"

class AWeapon;
/**
 * 
 */
UCLASS()
class VAMPIRES_API UStarterWeaponButtonDataObject : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText WeaponName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText WeaponDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UTexture2D> WeaponIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AWeapon> WeaponTemplate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<AWeapon> WeaponInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UUserWidget> Parent;

	void SetData(AWeapon* Weapon, UUserWidget* ParentWidget);
	void SetData(TSubclassOf<AWeapon> Weapon, UUserWidget* ParentWidget);
	void SetData(FText NewWeaponName, FText NewWeaponDescription, TObjectPtr<UTexture2D> NewWeaponIcon, UUserWidget* ParentWidget);
};
