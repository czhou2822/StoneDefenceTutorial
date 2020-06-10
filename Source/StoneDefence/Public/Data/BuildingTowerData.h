#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "BuildingTowerData.generated.h"

/**
 *
 */

USTRUCT()
struct FBuildingTower
{
	GENERATED_BODY()

		UPROPERTY(SaveGame)
		int32 TowerID;

	UPROPERTY(SaveGame)
		int32 NeedGold;

	UPROPERTY(SaveGame)
		int32 TowersPerpareBuildingNumber;

	UPROPERTY(SaveGame)
		int32 TowersConstructionNumber;

	UPROPERTY(SaveGame)
		float MaxConstructionTowersCD;

	UPROPERTY(SaveGame)
		float CurrentConstructionTowersCD;

	UPROPERTY(SaveGame)
		class UTexture2D* ICO;

	UPROPERTY(SaveGame)
		bool bDragICO;

	UPROPERTY(SaveGame)
		int32 bLockCD;

	UPROPERTY(SaveGame)
		bool bCallUpdateTowerInfo;

public:
	FBuildingTower();

	void Init();

	float GetTowerConstructionTimePercentage();

	bool IsValid();

	void ResetCD();


};