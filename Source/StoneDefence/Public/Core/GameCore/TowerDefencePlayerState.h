// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Data/Save/PlayerSaveData.h"
#include "Data/Save/GameSaveData.h"
#include "Data/BuildingTowerData.h"
#include "TowerDefencePlayerState.generated.h"


/**
 * 
 */
UCLASS()
class STONEDEFENCE_API ATowerDefencePlayerState : public APlayerState
{
	GENERATED_BODY()


private:
	UPROPERTY()
	FBuildingTower BuildingTowerNULL;


protected:
	UPROPERTY()
	UPlayerSaveData* SaveData;

public:

	//Íæ¼Ò¼¼ÄÜ
	UPROPERTY()
	UDataTable* PlayerSkillDataTable;

	TArray<FPlayerSkillData*> CachePlaterSkillData;

public:
	ATowerDefencePlayerState();

	virtual void BeginPlay() override;

	const TArray<FPlayerSkillData*>& GetPlayerSkillDataFormTable();

	const FPlayerSkillData* GetPlayerSkillDataFormTable(const int32& PlayerSkillID);

	FPlayerSkillData* GetPlayerSkillData(const FGuid& PlayerSkillGUID);

	bool IsVerificationSkill(const FGuid& SlotID);

	void UsePlayerSkill(const FGuid& SlotID);

	void AddPlayerSkill(const FGuid* Guid, int32 SkillID);

	FBuildingTower& GetBuildingTower(const FGuid& ID);

	FPlayerData& GetPlayerData();

	const FBuildingTower& AddBuildingTower(const FGuid& ID, const FBuildingTower& Data);

	const TArray<const FGuid*> GetBuildingTowersID();

	void RequestInventorySlotSwap(const FGuid& A, const FGuid& B);

	FBuildingTower& GetBuildingTowerNULL();

	UPlayerSaveData* GetSaveData();

	FPlayerSkillData* GetSkillData(const FGuid& SkillGuid);

	const TArray<const FGuid*> GetSkillDataID();

	UFUNCTION(/*Server*/)
	void TowersPerpareBuildingNumber(const FGuid& InventoryGUID);

	UFUNCTION(/*Server*/)
	void SetTowersDragICOState(const FGuid& InventoryGUID, bool bDragICO);
	

};
