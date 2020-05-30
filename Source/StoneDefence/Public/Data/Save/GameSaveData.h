// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/CharacterData.h"
#include "Data/GameData.h"
#include "Data/PlayerData.h"
#include "GameFramework/SaveGame.h"
#include "GameSaveData.generated.h"

//data for tower in inventory
USTRUCT()
struct FBuildingTower
{
	GENERATED_BODY()

	UPROPERTY(SaveGame)
	int32 TowerID;

	UPROPERTY(SaveGame)
	int32 NeedGold;

	UPROPERTY(SaveGame)
	int32 TowersPerpareBuildingNumber;

	UPROPERTY(SaveGame)
	int32 TowersConstructionNumber;

	UPROPERTY(SaveGame)
	float MaxConstructionTowersCD;

	UPROPERTY(SaveGame)
	float CurrentConstructionTowersCD;

	UPROPERTY(SaveGame)
	UTexture2D* ICO;

	UPROPERTY(SaveGame)
	bool bDragICO;

	UPROPERTY(SaveGame)
	int32 bLockCD;

	UPROPERTY(SaveGame)
	bool bCallUpdateTowerInfo;

public:
	FBuildingTower();

	void Init();
		
	float GetTowerConstructionTimePercentage();

	bool IsValid();

	void ResetCD();
	

};




/**
 * 
 */
UCLASS()
class STONEDEFENCE_API UGameSaveData : public USaveGame
{
	GENERATED_BODY()



public:

	UPROPERTY(SaveGame)
	TMap<FGuid, FCharacterData> CharacterData;

	UPROPERTY(SaveGame)
	TMap<FGuid, FBuildingTower> BuildingTowers;

	UPROPERTY(SaveGame)
	FPlayerData PlayerData;

	UPROPERTY(SaveGame)
	FGameInstanceData GameData;

	
};
