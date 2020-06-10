// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "StoneDefenceGameMode.generated.h"


class ATowers;
class AMonsters;
class ARuleOfTheCharacter;
class UDataTable;
/**
 * 
 */
UCLASS()
class STONEDEFENCE_API AStoneDefenceGameMode : public AGameMode
{
	GENERATED_BODY()

protected:

	ARuleOfTheCharacter* SpawnCharacter(int32 CharacterID, int32 CharacterLevel, UDataTable* InCharacterData, const FVector& Location, const FRotator& Rotator);

	template<class T>
	T* SpawnCharacter(int32 CharacterID, int32 CharacterLevel, UDataTable* InCharacterData, const FVector& Location, const FRotator& Rotator)
	{
		return Cast<T>(SpawnCharacter(CharacterID, CharacterLevel, InCharacterData, Location, Rotator));
	}


public:
	AStoneDefenceGameMode();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	void SpawnMonsterRule(float DeltaSeconds);

	void SpawnMainTowerRule();

	UFUNCTION(BlueprintCallable, Category = Spawn)
		AMonsters* SpawnMonster(int32 CharacterID, int32 CharacterLevel, const FVector& Location, const FRotator& Rotator);

	UFUNCTION(BlueprintCallable, Category = Spawn)
		ATowers* SpawnTower(int32 CharacterID, int32 CharacterLevel, const FVector& Location, const FRotator& Rotator);


};
