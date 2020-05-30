// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameData.generated.h"


USTRUCT()
struct FGameInstanceData
{
	GENERATED_USTRUCT_BODY()


	FGameInstanceData();

	void Init();

	//bool IsValid();

	UPROPERTY(SaveGame)
	int32 NumberOfMonster;

	UPROPERTY(SaveGame)
	int32 GameDifficulty;

	UPROPERTY(SaveGame)
	uint8 bAllMainTowerDie : 1;

	UPROPERTY(Transient)
	uint8 GameOver : 1;

	UPROPERTY(Transient)
	uint8 bCurrentLevelMissionSuccess : 1;

	UPROPERTY(SaveGame)
	int32 SpawnMonsterStage;

	UPROPERTY(SaveGame)
	int32 CurrentLevel;

	UPROPERTY(SaveGame)
	float TimeInterval;

	UPROPERTY(SaveGame)
	int32 CurrentStagesAreMonsters;

	UPROPERTY(SaveGame)
	TArray<int32> PerNumberOfMonsters;

	UPROPERTY(SaveGame)
	float GameCount;

	UPROPERTY(SaveGame)
	float MaxGameCount;

	UPROPERTY(Transient)
	float GoldGrowthTime;

	UPROPERTY(Transient)
	float GoldGrowthMaxTime;

	UPROPERTY(SaveGame)
	int32 KillMonstersNumber;

	UPROPERTY(SaveGame)
	int32 KillMonsterBossNumber;

	UPROPERTY(SaveGame)
	int32 TowersDeathNumber;

	UPROPERTY(SaveGame)
	int32 MainTowersDeathNumber;

	float GetPerOfRemMonsters();

	int32 GetMaxMonstersNumber();

};