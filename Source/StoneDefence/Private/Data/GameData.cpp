#include "Data/GameData.h"


FGameInstanceData::FGameInstanceData()
{

	Init();
}

void FGameInstanceData::Init()
{
	GameDifficulty = 0;
	bAllMainTowerDie = false;
	bGameOver = false;
	bCurrentLevelMissionSuccess = false;
	CurrentLevel = INDEX_NONE;
	TimeInterval = 0.5f;
	GameCount = 6000;
	MaxGameCount = 0;
	GoldGrowthTime = 1.f;
	GoldGrowthMaxTime = 1.5f;
	KillMonstersNumber = 0;
	KillMonsterBossNumber = 0; 
	TowersDeathNumber = 0;
	MainTowersDeathNumber = 0;
	CurrentSpawnMonsterTime = 0.f;
	MaxMonster = 100;
	MaxStagesAreMonsters = 4;
}

int32 FGameInstanceData::GetSurplusMonsters()
{
	int32 InSurplus = 0;
	for (auto &Tmp:PerNumberOfMonsters)
	{
		InSurplus += Tmp;
	}
	return InSurplus;
}

float FGameInstanceData::GetPerOfRemMonsters()
{
	if (MaxMonster)
	{
		return GetSurplusMonsters() / (float)MaxMonster;
	}
	return 0.f;
}

void FGameInstanceData::StageDecision()
{
	int32 CurrentStagesAreMonsters = PerNumberOfMonsters.Num() - 1;
	if (PerNumberOfMonsters.Num())
	{
		if (PerNumberOfMonsters[CurrentStagesAreMonsters] > 0)
		{
			PerNumberOfMonsters[CurrentStagesAreMonsters]--;
		}
		else
		{
			PerNumberOfMonsters.RemoveAt(CurrentStagesAreMonsters);
		}
	}
	else
	{
		bCurrentLevelMissionSuccess = true;
	}
}



void FGameInstanceData::AssignedMonsterAmount()
{
	int32 CurrentMonsterNumber = MaxMonster;

	int32 CurrentStagesNumber = MaxStagesAreMonsters;

	int32 CurrentAssignedNum = 0;

	if (CurrentMonsterNumber > 1)
	{
		for (int32 i = 0; i < MaxStagesAreMonsters; i++)  //each wave
		{
			float StagesNumber = (float)CurrentMonsterNumber / (float)CurrentStagesNumber;

			CurrentStagesNumber--;
			if (CurrentStagesNumber > 0)
			{
				CurrentAssignedNum = FMath::RandRange(StagesNumber / 2, StagesNumber);
			}
			else
			{
				CurrentAssignedNum = StagesNumber;
			}

			PerNumberOfMonsters.Add(CurrentAssignedNum);

			CurrentMonsterNumber -= CurrentAssignedNum;
		}
	}

	else
	{
		PerNumberOfMonsters.Add(CurrentAssignedNum);
	}


}

void FGameInstanceData::ResetSpawnMonsterTime()
{
	CurrentSpawnMonsterTime = 0.0f;
}

//bool FGameInstanceData::IsValid()
//{
//	return false;
//}
