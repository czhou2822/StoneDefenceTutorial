// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Core/RuleOfTheAIController.h"
#include "MonsterAIController.generated.h"

class ARuleOfTheCharacter;

/**
 * 
 */
UCLASS()
class STONEDEFENCE_API AMonsterAIController : public ARuleOfTheAIController
{
	GENERATED_BODY()




public:
	virtual AActor* FindTarget();

	virtual void AttackTarget(ARuleOfTheCharacter* AttackTarget);

};
