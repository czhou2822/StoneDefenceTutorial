#include "Data/GameData.h"


FGameInstanceData::FGameInstanceData()
{

	Init();
}

void FGameInstanceData::Init()
{
	NumberOfMonster = 0;
	GameDifficulty = 0;
	bAllMainTowerDie = false;
	GameOver = false;
	bCurrentLevelMissionSuccess = false;
	SpawnMonsterStage = 0;
	CurrentLevel = INDEX_NONE;
	TimeInterval = 0.5f;
	CurrentStagesAreMonsters = 0;
	GameCount = 6000;
	MaxGameCount = 0;
	GoldGrowthTime = 1.f;
	GoldGrowthMaxTime = 1.5f;
	KillMonstersNumber = 0;
	KillMonsterBossNumber = 0; 
	TowersDeathNumber = 0;
	MainTowersDeathNumber = 0;
}

float FGameInstanceData::GetPerOfRemMonsters()
{
	int32 MaxMonsterNumber = GetMaxMonstersNumber();
	if (MaxMonsterNumber)
	{
		return (float)NumberOfMonster / (float)MaxMonsterNumber;
	}
	return 0.f;
}

int32 FGameInstanceData::GetMaxMonstersNumber()
{
	int32 MaxMonsterNumber = 0;
	for (auto& Tmp : PerNumberOfMonsters)
	{
		MaxMonsterNumber += Tmp;
	}
	return MaxMonsterNumber;
}

//bool FGameInstanceData::IsValid()
//{
//	return false;
//}
