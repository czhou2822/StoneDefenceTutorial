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
	ATowerDefencePlayerState();

	FBuildingTower& GetBuildingTower(const FGuid& ID);

	FPlayerData& GetPlayerData();

	const FBuildingTower& AddBuildingTower(const FGuid& ID, const FBuildingTower& Data);

	const TArray<const FGuid*> GetBuildingTowersID();

	void RequestInventorySlotSwap(const FGuid& A, const FGuid& B);

	FBuildingTower& GetBuildingTowerNULL();

	UPlayerSaveData* GetSaveData();

	
};
