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
	static ConstructorHelpers::FObjectFinder<UDataTable> MyTable_Skill(TEXT("/Game/GameData/CharacterSkillData"));


	AITowerCharacterData = MyTable_Towers.Object;
	AIMonsterCharacterData = MyTable_Monsters.Object;
	SkillCharacterData = MyTable_Skill.Object;


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



 FCharacterData &ATowerDefenceGameState::AddCharacterData(const FGuid& ID, const FCharacterData& Data)
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

const TArray<FCharacterData*>& ATowerDefenceGameState::GetTowerDataFormTable()
{
	if (!CacheTowerData.Num())
	{
		AITowerCharacterData->GetAllRows(TEXT("Character Data"), CacheTowerData);
	}

	return CacheTowerData;

}

const TArray<FCharacterData*>& ATowerDefenceGameState::GetMonsterDataFormTable()
{
	if (!CacheMonsterData.Num())
	{
		AIMonsterCharacterData->GetAllRows(TEXT("Character Data"), CacheMonsterData);
	}

	return CacheMonsterData;
}



const FCharacterData& ATowerDefenceGameState::GetCharacterDataByID(int32 ID, ECharacterType Type)
{
	auto GetMyCharacterData = [&](const TArray<FCharacterData*>& Data, int32 ID) -> const FCharacterData&
	{
		for (const auto& Tmp : Data)
		{
			if (Tmp->ID == ID)
			{
				return *Tmp;
			}
		}

		return CharacterDataNULL;
	};

	switch (Type)
	{
		case ECharacterType::TOWER:
		{
			const TArray<FCharacterData*> &Data = GetTowerDataFormTable();
			return GetMyCharacterData(Data, ID);
		}
		case ECharacterType::MONSTER:
		{
			const TArray<FCharacterData*>& Data = GetMonsterDataFormTable();
			return GetMyCharacterData(Data, ID);

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

const TArray<FSkillData*>& ATowerDefenceGameState::GetSkillDataFormTable()
{
	if (!CacheSkillData.Num())
	{
		SkillCharacterData->GetAllRows(TEXT("Skill Data"), CacheSkillData);
	}

	return CacheSkillData;
}



FSkillData& ATowerDefenceGameState::AddSkillData(const FGuid& CharacterID, const FGuid& SkillID, const FSkillData& Data)
{
	FCharacterData& InCharacterData = GetCharacterData(CharacterID);
	if (InCharacterData.IsValid())
	{
		return InCharacterData.AdditionalSkillData.Add(SkillID, Data);
	}

	return SkillDataNULL;
}

FSkillData& ATowerDefenceGameState::GetSkillData(const FGuid& SkillID)
{
	for (auto& Tmp : GetSaveData()->CharacterData)
	{
		if (Tmp.Value.AdditionalSkillData.Contains(SkillID))
		{
			return Tmp.Value.AdditionalSkillData[SkillID];
		}
	}
	return SkillDataNULL;
}

const FSkillData* ATowerDefenceGameState::GetSkillData(const int& SkillID)
{
	const TArray<FSkillData*>& SkillArray = GetSkillDataFormTable();
	for (const auto& Tmp : SkillArray)
	{
		if (SkillID == Tmp->ID)
		{
			return Tmp;
		}
	}
	return nullptr;
}

FSkillData& ATowerDefenceGameState::GetSkillData(const FGuid& CharacterID, const FGuid& SkillID)
{
	FCharacterData& InCharacterData = GetCharacterData(CharacterID);
	if (InCharacterData.IsValid())
	{
		if (InCharacterData.AdditionalSkillData.Contains(SkillID))
		{
			return InCharacterData.AdditionalSkillData[SkillID];
		}
	}

	return SkillDataNULL;
}

int32 ATowerDefenceGameState::RemoveSkillData(const FGuid& SkillID)
{
	for (auto& Tmp : GetSaveData()->CharacterData)
	{
		return Tmp.Value.AdditionalSkillData.Remove(SkillID);
	}
	return INDEX_NONE;
}


void ATowerDefenceGameState::AddSkillDataTemplateToCharacterData(const FGuid& CharacterID, int32 SkillID)
{
	if (const FSkillData* InData = GetSkillData(SkillID))
	{
		for (auto& Tmp : GetSaveData()->CharacterData)
		{
			if (CharacterID == Tmp.Key)
			{
				Tmp.Value.CharacterSkill.Add(*InData);
				Tmp.Value.CharacterSkill[Tmp.Value.CharacterSkill.Num() - 1].ResetCD();
				break;
			}
		}
	}

}

bool ATowerDefenceGameState::SetSubmissionDataType(FGuid CharacterID, int32 Skill, ESubmissionSkillRequestType Type)
{
	FCharacterData& InCharacterData = GetCharacterData(CharacterID);
	if (InCharacterData.IsValid())
	{
		for (auto &Tmp : InCharacterData.CharacterSkill)
		{
			if (Skill == Tmp.ID)
			{
				Tmp.SubmissionSkillRequestType = Type;
				return true;
			}
		}
	}
	return false;
}

bool ATowerDefenceGameState::IsVerificationSkillTemplate(const FGuid& CharacterID, int32 SkillID)
{
	const FCharacterData& InData = GetCharacterData(CharacterID);
	if (InData.IsValid())
	{
		return IsVerificationSkillTemplate(InData, SkillID);
	}

	return false;
}



bool ATowerDefenceGameState::IsVerificationSkillTemplate(const FCharacterData& CharacterData, int32 SkillID)
{
	for (auto& InSkill : CharacterData.CharacterSkill)
	{
		if (InSkill.ID == SkillID)
		{
			return true;
		}
	}
	return false;
}


bool ATowerDefenceGameState::IsVerificationSkill(const FCharacterData& CharacterSkill, int32 SkillID)
{

	for (auto& InSkill : CharacterSkill.AdditionalSkillData)
	{
		if (InSkill.Value.ID == SkillID)
		{
			return true;
		}
	}

	return false;
}

bool ATowerDefenceGameState::IsVerificationSkill(const FGuid& CharacterID, int32 SkillID)
{
	const FCharacterData& InData = GetCharacterData(CharacterID);

	if (InData.IsValid())
	{
		return IsVerificationSkill(InData, SkillID);
	}
	return false;
}

void ATowerDefenceGameState::AddSkill(const FGuid& CharacterGUID, int32& InSkillID)
{

}

void ATowerDefenceGameState::AddSkill(TPair<FGuid, FCharacterData>& InOwner, FSkillData& InSkill)
{
	if (!IsVerificationSkill(InOwner.Value, InSkill.ID))
	{
		FGuid MySkillID = FGuid::NewGuid();

		InOwner.Value.AdditionalSkillData.Add(MySkillID, InSkill).ResetDuration();

		StoneDefenceUtils::CallUpdateAllClient(GetWorld(), [&](ATowerDefencePlayerController* MyPlayerController)
		{
			MyPlayerController->AddSkillSlot_Server(InOwner.Key, MySkillID);
		});
	}



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