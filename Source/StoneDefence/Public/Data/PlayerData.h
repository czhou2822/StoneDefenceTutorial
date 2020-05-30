// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerData.generated.h"

USTRUCT()
struct FPlayerSkillData
{
	GENERATED_USTRUCT_BODY()

	FPlayerSkillData();

	void Init();

	bool IsValid();

	UPROPERTY(SaveGame)
	int32 SkillID;

	UPROPERTY(SaveGame)
	float SkillCD;

	UPROPERTY(SaveGame)
	float MaxSkillCD;

	UPROPERTY(SaveGame)
	int32 SkillNumber;


};

USTRUCT()
struct FPlayerData
{
	GENERATED_USTRUCT_BODY()

	FPlayerData();

	void Init();

	bool IsValid();

	UPROPERTY(SaveGame)
	FName PlayerName;

	UPROPERTY(SaveGame)
	FString Account;

	UPROPERTY(SaveGame)
	int32 PlayerID;

	UPROPERTY(SaveGame)
	int32 GameGold;

	UPROPERTY(SaveGame)
	int32 Diamonds;

	UPROPERTY(SaveGame)
	int32 Copper;

	UPROPERTY(SaveGame)
	TArray<int32> SkillIDs;

	UPROPERTY(SaveGame)
	TArray<FPlayerSkillData> SkillData;

};



