// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "RuleOfTheDamageType.generated.h"

/**
 * 
 */
UCLASS()
class STONEDEFENCE_API URuleOfTheDamage : public UDamageType
{
	GENERATED_BODY()

public:
	const struct FSkillData* SkillData = nullptr;
	
};
