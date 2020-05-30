// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "GameSaveSlotList.generated.h"

USTRUCT()
struct FSaveSlot
{
	GENERATED_USTRUCT_BODY()

	FSaveSlot();

	//Save content and date
	UPROPERTY(SaveGame)
	FText DataText;

	//is valid
	UPROPERTY(SaveGame)
	bool bSave;



};


USTRUCT()
struct FSaveSlotList
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(SaveGame)
	TMap<int32, FSaveSlot> Slots;

	TMap<int32, float> DegreeOfCompletion;

	FSaveSlotList();

	int32 GetSerialNumber();

	bool RemoveAtGameData(int32 SlotNumber);

	bool AddGameData(int32 SlotNumber);

	bool AddGameDataByNumber(int32 SlotNumber);


};


/**
 *
 */
UCLASS()
class STONEDEFENCE_API UGameSaveSlotList : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(SaveGame)
	FSaveSlotList SlotList;
};