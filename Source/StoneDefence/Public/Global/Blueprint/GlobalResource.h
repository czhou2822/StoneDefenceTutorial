// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GlobalResource.generated.h"


/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)

class STONEDEFENCE_API UGlobalResource : public UObject
{
	GENERATED_BODY()

public:
	float TestValue = 0.f;
};
