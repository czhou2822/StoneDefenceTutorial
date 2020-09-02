// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "Data/CharacterData.h"
#include "Data/SkillData.h"
#include "Data/save/GameSaveData.h"
#include "Data/GameData.h"
#include "StoneDefence/StoneDefenceType.h"
#include "TowerDefenceGameState.generated.h"



class ARuleOfTheCharacter;
class AMonsters;
class ATowers;
class UDataTable;
class UGameSaveData;
class UGameSaveSlotList;
struct FSkillData;

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
	UDataTable* SkillCharacterData;

	UPROPERTY()
	UGameSaveData* SaveData;

	UPROPERTY()
	UGameSaveSlotList* SlotList;

	TArray<FCharacterData*> CacheTowerData;

	TArray<FCharacterData*> CacheMonsterData;

	TArray<FSkillData*> CacheSkillData;

	FCharacterData CharacterDataNULL;

	FSkillData SkillDataNULL;

protected:

	UGameSaveData* GetSaveData();

	UGameSaveSlotList* GetGameSaveSlotList();


public:

	ATowerDefenceGameState();

	FCharacterData& AddCharacterData(const FGuid& ID, const FCharacterData& Data);

	bool RemoveCharacterData(const FGuid& ID);

	FCharacterData& GetCharacterData(const FGuid& ID);

	const TArray<FCharacterData*>& GetTowerDataFormTable();

	const TArray<FCharacterData*>& GetMonsterDataFormTable();

	const FCharacterData& GetCharacterDataByID(int32 ID, ECharacterType Type = ECharacterType::TOWER);

	FGameInstanceData& GetGameData();

	FCharacterData& GetCharacterDataNULL();

	const TArray<FSkillData*>& GetSkillDataFormTable();

	//dynamic skills
	FSkillData& AddSkillData(const FGuid& CharacterID, const FGuid& SkillID, const FSkillData& Data);
	
	FSkillData& GetSkillData(const FGuid& SkillID);

	const FSkillData* GetSkillData(const int& SkillID);

	FSkillData& GetSkillData(const FGuid& CharacterID, const FGuid& SkillID);

	int32 RemoveSkillData(const FGuid& SkillID);

	UFUNCTION(/*Server*/)
	void AddSkillDataTemplateToCharacterData(const FGuid& CharacterID, int32 SkillID);
	UFUNCTION(/*Server*/)
	bool SetSubmissionDataType(FGuid CharacterID, int32 Skill, ESubmissionSkillRequestType Type);

	bool IsVerificationSkillTemplate(const FGuid& CharacterID, int32 SkillID);
	bool IsVerificationSkillTemplate(const FCharacterData& CharacterSkill, int32 SkillID);
	bool IsVerificationSkill(const FCharacterData& CharacterData, int32 SkillID);
	bool IsVerificationSkill(const FGuid& CharacterID, int32 SkillID);

	void AddSkill(TPair<FGuid, FCharacterData>& InOwner, FSkillData& InSkill);




	UFUNCTION(BlueprintCallable, Category = SaveData)
	bool SaveGameData(int32 SaveNumber);

	UFUNCTION(BlueprintCallable, Category = SaveData)
	bool ReadGameData(int32 SaveNumber);







};
