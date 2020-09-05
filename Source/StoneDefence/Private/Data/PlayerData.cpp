// Fill out your copyright notice in the Description page of Project Settings.

#include "Data/PlayerData.h"
#include "StoneDefence/StoneDefenceType.h"


FPlayerData::FPlayerData()
{
	Init();
}

void FPlayerData::Init()
{
	PlayerID = INDEX_NONE;
	PlayerName = NAME_None;
	GameGold = 5000;
	Diamonds = 0;
	Copper = 0;
	Team = ETeam::RED;
	GameGoldTime = 0.f;
	MaxGameGoldTime = 1.24f;
	SkillIDs.Add(0);

}

bool FPlayerData::IsValid()
{
	return PlayerID != INDEX_NONE;
}

bool FPlayerData::IsAllowIncrease()
{
	return GameGoldTime >= MaxGameGoldTime;
}
