// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StoneDefence/StoneDefenceType.h"
#include "Data/CharacterData.h"
#include "GameFramework/GameState.h"
#include "data/Save/GameSaveSlotList.h"
#include "Data/save/GameSaveData.h"
#include "Data/CharacterData.h"
#include "Data/GameData.h"
#include "TowerDefenceGameState.generated.h"

extern FCharacterData CharacterDataNULL;
extern FBuildingTower BuildingTowerNULL;


class AMonsters;
class ATowers;
class UDataTable;
class ARuleOfTheCharacter;
class UGameSaveData;

/**
 * 
 */
UCLASS()
class STONEDEFENCE_API ATowerDefenceGameState : public AGameState
{
	GENERATED_BODY()
	


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
	

protected:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	ARuleOfTheCharacter* SpawnCharacter(int32 CharacterID, int32 CharacterLevel, UDataTable* InCharacterData, const FVector& Location, const FRotator& Rotator);

	template<class T>
	T* SpawnCharacter(int32 CharacterID, int32 CharacterLevel, UDataTable* InCharacterData, const FVector& Location, const FRotator& Rotator)
	{
		return Cast<T>(SpawnCharacter(CharacterID, CharacterLevel, InCharacterData, Location, Rotator));
	}

	UGameSaveData* GetSaveData();

	UGameSaveSlotList* GetGameSaveSlotList();

	void SpawnMonsterRule(float DeltaSeconds);



public:

	ATowerDefenceGameState();

	const FCharacterData& AddCharacterData(const FGuid& ID, const FCharacterData& Data);
	
	const FBuildingTower& AddBuildingTower(const FGuid& ID, const FBuildingTower& Data);

	bool RemoveCharacterData(const FGuid& ID);

	FCharacterData& GetCharacterData(const FGuid& ID);

	FBuildingTower& GetBuildingTower(const FGuid& ID);

	const TArray<const FGuid*> GetBuildingTowersID();

	bool GetTowerDataFormTable(TArray<const FCharacterData*>& Data);

	bool GetMonsterDataFormTable(TArray<const FCharacterData*>& Data);

	const FCharacterData& GetCharacterDataByID(int32 ID, ECharacterType Type = ECharacterType::TOWER);

	void RequestInventorySlotSwap(const FGuid& A, const FGuid& B);

	class AStaticMeshActor* SpawnTowersDoll(int32 ID);

	FPlayerData& GetPlayerData();

	FGameInstanceData& GetGameData();

	UFUNCTION(BlueprintCallable, Category = Spawn)
	AMonsters* SpawnMonster(int32 CharacterID, int32 CharacterLevel, const FVector& Location, const FRotator& Rotator);

	UFUNCTION(BlueprintCallable, Category = Spawn)
	ATowers* SpawnTower(int32 CharacterID, int32 CharacterLevel, const FVector& Location, const FRotator& Rotator);

	UFUNCTION(BlueprintCallable, Category = SaveData)
	bool SaveGameData(int32 SaveNumber);

	UFUNCTION(BlueprintCallable, Category = SaveData)
	bool ReadGameData(int32 SaveNumber);


};
