// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Data/save/GameSaveData.h"
#include "Data/PlayerSkillData.h"
#include "Data/BuildingTowerData.h"
#include "PlayerSaveData.generated.h"


/**
 * 
 */
UCLASS()
class STONEDEFENCE_API UPlayerSaveData : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(SaveGame)
	FPlayerData PlayerData;

	UPROPERTY(SaveGame)
	TMap<FGuid, FBuildingTower> BuildingTowers;

	UPROPERTY(SaveGame)
	TMap<FGuid, FPlayerSkillData> PlayerSkillData;
};
