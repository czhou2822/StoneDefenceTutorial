// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "StoneDefence/StoneDefenceType.h"
#include "Core/GameCore/TowerDefenceGameState.h"
#include "RuleCharacter.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class URuleCharacter : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class STONEDEFENCE_API IRuleCharacter
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual bool IsDead() = 0;
	virtual float GetHealth() = 0;
	virtual float GetMaxHealth() = 0;
	virtual bool IsTeam() = 0;

	virtual FCharacterData& GetCharacterData() = 0;
	virtual EGameCharacterType::Type GetType() = 0;
};