// Fill out your copyright notice in the Description page of Project Settings.


#include "StoneDefence/Public/Core/GameCore/TowerDefenceGameState.h"
#include "StoneDefence/StoneDefenceMacro.h"
#include "Data/CharacterData.h"
#include "Engine/World.h"
#include "Data/Save/GameSaveData.h"
#include "Character/CharacterCore/Towers.h"
#include "Character/CharacterCore/Monsters.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"
#include "Data/Save/GameSaveSlotList.h"
#include "StoneDefence/StoneDefenceUtils.h"


#if PLATFORM_WINDOWS
#pragma optimize("", off)
#endif

ATowerDefenceGameState::ATowerDefenceGameState()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> MyTable_Towers(TEXT("/Game/GameData/TowerData"));
	static ConstructorHelpers::FObjectFinder<UDataTable> MyTable_Monsters(TEXT("/Game/GameData/MonsterData"));

	AITowerCharacterData = MyTable_Towers.Object;
	AIMonsterCharacterData = MyTable_Monsters.Object;

	PrimaryActorTick.bCanEverTick = true;


}


UGameSaveSlotList* ATowerDefenceGameState::GetGameSaveSlotList()
{
	if (!SaveData)
	{
		SlotList = Cast<UGameSaveSlotList>(UGameplayStatics::LoadGameFromSlot(FString::Printf(TEXT("SlotList")), 0));
		if (!SlotList)
		{
			SlotList = Cast<UGameSaveSlotList>(UGameplayStatics::CreateSaveGameObject(UGameSaveSlotList::StaticClass()));
		}
	}
	return SlotList;
}


UGameSaveData* ATowerDefenceGameState::GetSaveData()
{
	if (!SaveData)
	{
		SaveData = Cast<UGameSaveData>(UGameplayStatics::CreateSaveGameObject(UGameSaveData::StaticClass()));
	}
	return SaveData;
}



const FCharacterData &ATowerDefenceGameState::AddCharacterData(const FGuid& ID, const FCharacterData& Data)
{
	return GetSaveData()->CharacterData.Add(ID, Data);
}

bool ATowerDefenceGameState::RemoveCharacterData(const FGuid& ID)
{
	return (bool)GetSaveData()->CharacterData.Remove(ID);
}

FCharacterData& ATowerDefenceGameState::GetCharacterData(const FGuid& ID)
{
	
	if (GetSaveData()->CharacterData.Contains(ID))
	{
		return GetSaveData()->CharacterData[ID];
	}

	SD_print(Error, "The current [%s] is invalid", *ID.ToString());

	return CharacterDataNULL;
}

bool ATowerDefenceGameState::GetTowerDataFormTable(TArray<const FCharacterData*>& Data)
{
	if (!CacheTowerData.Num())
	{
		AITowerCharacterData->GetAllRows(TEXT("Character Data"), CacheTowerData);
	}

	
	for (const auto& Tmp : CacheTowerData)
	{
		Data.Add(Tmp);
	}
	

	return Data.Num() > 0;
}

bool ATowerDefenceGameState::GetMonsterDataFormTable(TArray<const FCharacterData*>& Data)
{
	if (!CacheMonsterData.Num())
	{
		AIMonsterCharacterData->GetAllRows(TEXT("Character Data"), CacheMonsterData);
	}

	for (const auto& Tmp : CacheMonsterData)
	{
		Data.Add(Tmp);
	}


	return Data.Num() > 0;
}

const FCharacterData& ATowerDefenceGameState::GetCharacterDataByID(int32 ID, ECharacterType Type)
{
	TArray<const FCharacterData*> Data;

	switch (Type)
	{
		case ECharacterType::TOWER:
		{
			GetTowerDataFormTable(Data);
			break;
		}
		case ECharacterType::MONSTER:
		{
			GetMonsterDataFormTable(Data);
			break;
		}
	}

	for (const auto& Tmp : Data)
	{
		if (Tmp->ID == ID)
		{
			return *Tmp;
		}
	}


	return CharacterDataNULL;


}

FGameInstanceData& ATowerDefenceGameState::GetGameData()
{
	return GetSaveData()->GameData;
}

FCharacterData& ATowerDefenceGameState::GetCharacterDataNULL()
{
	return CharacterDataNULL;
}



bool ATowerDefenceGameState::SaveGameData(int32 SaveNumber)
{
	if (SaveData && SlotList)
	{
		SlotList->SlotList.AddGameDataByNumber(SaveNumber);

		return UGameplayStatics::SaveGameToSlot(SlotList, FString::Printf(TEXT("SlotList")), 0)
			&& UGameplayStatics::SaveGameToSlot(SaveData, FString::Printf(TEXT("SaveSlot_%i"),SaveNumber), 0);
	}

	return false;
}

bool ATowerDefenceGameState::ReadGameData(int32 SaveNumber)
{
	SaveData = Cast<UGameSaveData>(UGameplayStatics::LoadGameFromSlot(FString::Printf(TEXT("SaveSlot_%i"), SaveNumber), 0));

	return SaveData != NULL;
}

#if PLATFORM_WINDOWS
#pragma optimize ("" ,on)
#endif