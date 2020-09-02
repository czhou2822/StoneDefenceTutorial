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
	GameGold = 0;
	Diamonds = 0;
	Copper = 0;
	MaxGameGoldTime = 1.24f;
	GameGoldTime = 0.f;
	Team = ETeam::RED;

}

bool FPlayerData::IsValid()
{
	return PlayerID != INDEX_NONE;
}

bool FPlayerData::IsAllowIncrease()
{
	return GameGoldTime >= MaxGameGoldTime;
}
