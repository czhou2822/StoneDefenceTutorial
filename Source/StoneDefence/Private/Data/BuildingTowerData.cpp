#pragma once

#include "Data/BuildingTowerData.h"


FBuildingTower::FBuildingTower()
{
	Init();
}

void FBuildingTower::Init()
{
	TowerID = INDEX_NONE;
	NeedGold = INDEX_NONE;
	TowersPerpareBuildingNumber = 0.0f;
	TowersConstructionNumber = 0.0f;
	MaxConstructionTowersCD = 0.0f;
	CurrentConstructionTowersCD = 0.0f;
	ICO = NULL;
	bDragICO = false;
	bLockCD = false;
	bCallUpdateTowerInfo = false;
}

float FBuildingTower::GetTowerConstructionTimePercentage()
{
	return MaxConstructionTowersCD ? CurrentConstructionTowersCD / MaxConstructionTowersCD : 0.f;
}

bool FBuildingTower::IsValid()
{
	return TowerID != INDEX_NONE;
}

void FBuildingTower::ResetCD()
{
	CurrentConstructionTowersCD = MaxConstructionTowersCD;
}