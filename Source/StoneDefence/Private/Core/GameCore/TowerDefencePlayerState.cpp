// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/GameCore/TowerDefencePlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "StoneDefence/StoneDefenceUtils.h"
#include "Data/PlayerData.h"
#include "Core/GameCore/TowerDefencePlayerController.h"

#include "UObject/ConstructorHelpers.h"
ATowerDefencePlayerState::ATowerDefencePlayerState()
{

	static ConstructorHelpers::FObjectFinder<UDataTable> MyTable_Skill(TEXT("/Game/GameData/PlayerSkillData"));

	PlayerSkillDataTable = MyTable_Skill.Object;


}

void ATowerDefencePlayerState::BeginPlay()
{
	Super::BeginPlay();

	//物品栏的塔slot
	for (int32 i = 0; i < 21; i++)
	{
		GetSaveData()->BuildingTowers.Add(FGuid::NewGuid(), FBuildingTower());
	}

	for (int32 i = 0; i < 10; i++)
	{
		GetSaveData()->PlayerSkillData.Add(FGuid::NewGuid(), FPlayerSkillData());
	}
}

const TArray<FPlayerSkillData*>& ATowerDefencePlayerState::GetPlayerSkillDataFormTable()
{
	if (!CachePlaterSkillData.Num())
	{
		PlayerSkillDataTable->GetAllRows(TEXT("Player Skill Data"), CachePlaterSkillData);
	}

	return CachePlaterSkillData;

}

const FPlayerSkillData* ATowerDefencePlayerState::GetPlayerSkillDataFormTable(const int32& PlayerSkillID)
{
	
	const TArray<FPlayerSkillData*>& InSkillData = GetPlayerSkillDataFormTable();

	for (auto& Tmp : InSkillData)
	{
		if (Tmp->ID == PlayerSkillID)
		{
			return Tmp;
		}
	}
	return nullptr;


}

FPlayerSkillData* ATowerDefencePlayerState::GetPlayerSkillData(const FGuid& PlayerSkillGUID)
{
	if (GetSaveData()->PlayerSkillData.Contains(PlayerSkillGUID))
	{
		return &GetSaveData()->PlayerSkillData[PlayerSkillGUID];
	}

	return nullptr;
}

bool ATowerDefencePlayerState::IsVerificationSkill(const FGuid& SlotID)
{
	if (FPlayerSkillData * InData = GetPlayerSkillData(SlotID))
	{
		if (InData->IsValid() && InData->SkillNumber > 0 && InData->GetCDPercent() <= 0.f)
		{
			return true;
		}
	}
	return false;
}

void ATowerDefencePlayerState::UsePlayerSkill(const FGuid& SlotID)
{
	if (FPlayerSkillData* InData = GetPlayerSkillData(SlotID))
	{
		if (InData->IsValid())
		{
			InData->SkillNumber--;

			InData->ResetCD();

			StoneDefenceUtils::CallUpdateAllClient(GetWorld(), [&](ATowerDefencePlayerController* MyPlayerController)
			{
				MyPlayerController->SpawnPlayerSkill_Client(InData->ID);
			});
		}
	}
}

void ATowerDefencePlayerState::AddPlayerSkill(const FGuid* Guid, int32 SkillID)
{
	if (const FPlayerSkillData* FSkill = GetPlayerSkillDataFormTable(SkillID))
	{
		GetSaveData()->PlayerSkillData[*Guid] = *FSkill;

		StoneDefenceUtils::CallUpdateAllClient(GetWorld(), [&](ATowerDefencePlayerController* MyPlayerController)
		{
			MyPlayerController->UpdatePlayerSkill_Client(*Guid, false);
		});
	}

}

FBuildingTower& ATowerDefencePlayerState::GetBuildingTower(const FGuid& ID)
{
	if (GetSaveData()->BuildingTowers.Contains(ID))
	{
		return GetSaveData()->BuildingTowers[ID];
	}

	//SD_print(Error, "The current [%s] is invalid", *ID.ToString());

	return BuildingTowerNULL;
}

FPlayerData& ATowerDefencePlayerState::GetPlayerData()
{
	return GetSaveData()->PlayerData;
}

const FBuildingTower& ATowerDefencePlayerState::AddBuildingTower(const FGuid& ID, const FBuildingTower& Data)
{
	return GetSaveData()->BuildingTowers.Add(ID, Data);
}

const TArray<const FGuid*> ATowerDefencePlayerState::GetBuildingTowersID()
{
	TArray<const FGuid*> Towers;

	for (const auto& Tmp : GetSaveData()->BuildingTowers)
	{
		Towers.Add(&Tmp.Key);
	}

	return Towers;
}

void ATowerDefencePlayerState::RequestInventorySlotSwap(const FGuid& A, const FGuid& B)
{
	FBuildingTower& ASlot = GetBuildingTower(A);
	FBuildingTower& BSlot = GetBuildingTower(B);

	if (ASlot.IsValid())   //switch
	{
		FBuildingTower TmpSlot = ASlot;
		ASlot = BSlot;
		BSlot = TmpSlot;
	}
	else //move
	{
		ASlot = BSlot;
		BSlot.Init();
	}
}

FBuildingTower& ATowerDefencePlayerState::GetBuildingTowerNULL()
{
	return BuildingTowerNULL;
}

UPlayerSaveData* ATowerDefencePlayerState::GetSaveData()
{
	if (!SaveData)
	{
		SaveData = Cast<UPlayerSaveData>(UGameplayStatics::CreateSaveGameObject(UPlayerSaveData::StaticClass()));
	}
	return SaveData;
}

FPlayerSkillData* ATowerDefencePlayerState::GetSkillData(const FGuid& SkillGuid)
{
	if (GetSaveData()->PlayerSkillData.Contains(SkillGuid))
	{
		return &GetSaveData()->PlayerSkillData[SkillGuid];
	}

	//SD_print(Error, "The current [%s] is invalid", *SkillGuid.ToString());

	return nullptr;

}

const TArray<const FGuid*> ATowerDefencePlayerState::GetSkillDataID()
{
	TArray<const FGuid*> SkillIDs;
	for (const auto& Tmp : GetSaveData()->PlayerSkillData)
	{
		SkillIDs.Add(&Tmp.Key);
	}

	return SkillIDs;
}

void ATowerDefencePlayerState::TowersPerpareBuildingNumber(const FGuid& InventoryGUID)
{
	FBuildingTower& BT = GetBuildingTower(InventoryGUID);
	if (BT.IsValid()) //服务器验证 防止作弊
	{
		if (BT.NeedGold <= GetPlayerData().GameGold)
		{
			BT.TowersPerpareBuildingNumber++;
			GetPlayerData().GameGold -= BT.NeedGold;

			if (BT.CurrentConstructionTowersCD <= 0)
			{
				BT.ResetCD();
			}
		}
	}
}
void ATowerDefencePlayerState::SetTowersDragICOState(const FGuid& InventoryGUID, bool bDragICO)
{
	FBuildingTower& BT = GetBuildingTower(InventoryGUID);
	BT.bDragICO = bDragICO;
}

