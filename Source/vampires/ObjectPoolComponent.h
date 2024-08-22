// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ObjectPoolComponent.generated.h"


DECLARE_DELEGATE(FOnRetrieve)
DECLARE_DELEGATE(FOnReturn)

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class VAMPIRES_API UObjectPoolComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	FOnRetrieve OnRetrieve;
	FOnReturn OnReturn;
};
