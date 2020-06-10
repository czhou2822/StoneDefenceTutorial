// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "Data/CharacterData.h"
#include "Data/save/GameSaveData.h"
#include "Data/GameData.h"
#include "StoneDefence/StoneDefenceType.h"
#include "TowerDefenceGameState.generated.h"



class AMonsters;
class ATowers;
class UDataTable;
class ARuleOfTheCharacter;
class UGameSaveData;
class UGameSaveSlotList;

/**
 * 
 */
UCLASS()
class STONEDEFENCE_API ATowerDefenceGameState : public AGameState
{
	GENERATED_BODY()

	friend class AStoneDefenceGameMode;

private:
	//UPROPERTY()
	//TMap<uint32, FCharacterData> CharacterData;

	UPROPERTY()
	UDataTable* AITowerCharacterData;

	UPROPERTY()
	UDataTable* AIMonsterCharacterData;

	UPROPERTY()
	UGameSaveData* SaveData;

	UPROPERTY()
	UGameSaveSlotList* SlotList;

	TArray<FCharacterData*> CacheTowerData;

	TArray<FCharacterData*> CacheMonsterData;

	FCharacterData CharacterDataNULL;

	

protected:

	UGameSaveData* GetSaveData();

	UGameSaveSlotList* GetGameSaveSlotList();


public:

	ATowerDefenceGameState();

	FCharacterData& AddCharacterData(const FGuid& ID, const FCharacterData& Data);

	bool RemoveCharacterData(const FGuid& ID);

	FCharacterData& GetCharacterData(const FGuid& ID);

	bool GetTowerDataFormTable(TArray<const FCharacterData*>& Data);

	bool GetMonsterDataFormTable(TArray<const FCharacterData*>& Data);

	const FCharacterData& GetCharacterDataByID(int32 ID, ECharacterType Type = ECharacterType::TOWER);

	FGameInstanceData& GetGameData();

	FCharacterData& GetCharacterDataNULL();

	UFUNCTION(BlueprintCallable, Category = SaveData)
	bool SaveGameData(int32 SaveNumber);

	UFUNCTION(BlueprintCallable, Category = SaveData)
	bool ReadGameData(int32 SaveNumber);


};
