// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "TowerDefenceSelectLevelGameMode.generated.h"

/**
 * 
 */
UCLASS()
class STONEDEFENCE_API ATowerDefenceSelectLevelGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ATowerDefenceSelectLevelGameMode();

	virtual void BeginPlay() override;
	
};
