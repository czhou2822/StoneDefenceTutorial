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
	int32 MaxMonster;

	//how many waves in total
	UPROPERTY(SaveGame)
	int32 MaxStagesAreMonsters;

	//enemy counts in each wave, changes in runtime
	UPROPERTY(SaveGame)
	TArray<int32> PerNumberOfMonsters;

	UPROPERTY(SaveGame)
	int32 GameDifficulty;

	UPROPERTY(SaveGame)
	uint8 bAllMainTowerDie : 1;

	UPROPERTY(Transient)
	uint8 bGameOver : 1;

	UPROPERTY(Transient)
	uint8 bCurrentLevelMissionSuccess : 1;



	UPROPERTY(SaveGame)
	int32 CurrentLevel;

	UPROPERTY(SaveGame)
	float TimeInterval;

	UPROPERTY(SaveGame)
	float CurrentSpawnMonsterTime;


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

	int32 GetSurplusMonsters();

	float GetPerOfRemMonsters();

	void StageDecision();

	void AssignedMonsterAmount();

	FORCEINLINE bool IsAllowSpawnMonster() { return CurrentSpawnMonsterTime >= TimeInterval; }

	void ResetSpawnMonsterTime();
};