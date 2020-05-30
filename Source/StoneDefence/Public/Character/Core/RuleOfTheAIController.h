// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "RuleOfTheAIController.generated.h"

class ARuleOfTheCharacter;

/**
 * 
 */
UCLASS()
class STONEDEFENCE_API ARuleOfTheAIController : public AAIController
{
	GENERATED_BODY()


public:
	TWeakObjectPtr<class ARuleOfTheCharacter> Target;
	
public:
	
	virtual AActor* FindTarget() { return nullptr; };

	virtual void AttackTarget(ARuleOfTheCharacter * InTarget) {};




};
