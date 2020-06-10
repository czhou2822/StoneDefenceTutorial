// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/GameCore/TowerDefencePlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Data/PlayerData.h"

ATowerDefencePlayerState::ATowerDefencePlayerState()
{
	for (int32 i = 0; i < 21; i++)
	{
		GetSaveData()->BuildingTowers.Add(FGuid::NewGuid(), FBuildingTower());
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
