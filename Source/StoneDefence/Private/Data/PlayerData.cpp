// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/PlayerData.h"

FPlayerSkillData::FPlayerSkillData()
{
	Init();
}

void FPlayerSkillData::Init()
{
	SkillID = INDEX_NONE;
	SkillCD = 0;
	MaxSkillCD = 0.f;
	SkillNumber = INDEX_NONE;
}

bool FPlayerSkillData::IsValid()
{
	return SkillID != INDEX_NONE;
}

FPlayerData::FPlayerData()
{
	Init();
}

void FPlayerData::Init()
{
	PlayerID = INDEX_NONE;
	PlayerName = NAME_None;
	GameGold = 0;
	Diamonds = 0;
	Copper = 0;
}

bool FPlayerData::IsValid()
{
	return PlayerID != INDEX_NONE;
}
