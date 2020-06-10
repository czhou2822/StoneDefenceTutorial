// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/CharacterData.h"
#include "Data/GameData.h"
#include "Data/PlayerData.h"
#include "GameFramework/SaveGame.h"
#include "GameSaveData.generated.h"

//data for tower in inventory





/**
 * 
 */
UCLASS()
class STONEDEFENCE_API UGameSaveData : public USaveGame
{
	GENERATED_BODY()

public:

	UPROPERTY(SaveGame)
	TMap<FGuid, FCharacterData> CharacterData;

	UPROPERTY(SaveGame)
	FGameInstanceData GameData;

};
