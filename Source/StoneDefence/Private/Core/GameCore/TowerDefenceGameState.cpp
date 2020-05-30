// Fill out your copyright notice in the Description page of Project Settings.

#include "StoneDefence/Public/Core/GameCore/TowerDefenceGameState.h"
#include "StoneDefence/StoneDefenceMacro.h"
#include "Character/Core/RuleOfTheCharacter.h"
#include "Data/CharacterData.h"
#include "Engine/World.h"
#include "Data/Save/GameSaveData.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/StaticMeshActor.h"

FCharacterData CharacterDataNULL;
FBuildingTower BuildingTowerNULL;


ATowerDefenceGameState::ATowerDefenceGameState()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> MyTable_Towers(TEXT("/Game/GameData/TowerData"));
	static ConstructorHelpers::FObjectFinder<UDataTable> MyTable_Monsters(TEXT("/Game/GameData/MonsterData"));

	AITowerCharacterData = MyTable_Towers.Object;
	AIMonsterCharacterData = MyTable_Monsters.Object;

	PrimaryActorTick.bCanEverTick = true;

	for (int32 i = 0; i < 21; i++)
	{
		GetSaveData()->BuildingTowers.Add(FGuid::NewGuid(), FBuildingTower());
	}
}

void ATowerDefenceGameState::BeginPlay()
{
	Super::BeginPlay();

	//if (1)
	//{
	//	SaveData = Cast<UGameSaveData>(UGameplayStatics::CreateSaveGameObject(UGameSaveData::StaticClass()));
	//}

}

void ATowerDefenceGameState::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	GetGameData().GameCount -= DeltaSeconds;

}

UGameSaveSlotList* ATowerDefenceGameState::GetGameSaveSlotList()
{
	if (!SaveData)
	{
		SlotList = Cast<UGameSaveSlotList>(UGameplayStatics::LoadGameFromSlot(FString::Printf(TEXT("SlotList")), 0));
		if (!SlotList)
		{
			SlotList = Cast<UGameSaveSlotList>(UGameplayStatics::CreateSaveGameObject(UGameSaveSlotList::StaticClass()));
		}
	}
	return SlotList;
}

UGameSaveData* ATowerDefenceGameState::GetSaveData()
{
	if (!SaveData)
	{
		SaveData = Cast<UGameSaveData>(UGameplayStatics::CreateSaveGameObject(UGameSaveData::StaticClass()));
	}
	return SaveData;
}

ARuleOfTheCharacter* ATowerDefenceGameState::SpawnCharacter(
	int32 CharacterID, 
	int32 CharacterLevel, 
	UDataTable* InCharacterData, 
	const FVector& Location,
	const FRotator& Rotator)
{
	if (InCharacterData)
	{
		TArray<FCharacterData*> Data;
		InCharacterData->GetAllRows(TEXT("Character Data"), Data);
		auto GetCharacterData = [&](int32 ID) -> FCharacterData*
		{
			for (auto& Tmp : Data)
			{
				if (Tmp->ID == ID)
				{
					return Tmp;
				}
			}
			return nullptr;
		};

		if(FCharacterData* NewCharacterData = GetCharacterData(CharacterID))
		{
			UClass* NewClass = NewCharacterData->CharacterBlueprintKey.LoadSynchronous();

			if (GetWorld() && NewClass)
			{
				if (ARuleOfTheCharacter* RuleOfTheCharacter = GetWorld()->SpawnActor<ARuleOfTheCharacter>(NewClass, Location, Rotator))
				{
					NewCharacterData->UpdateHealth();
					AddCharacterData(RuleOfTheCharacter->GUID, *NewCharacterData);
				}
			}
		}

	}


	return nullptr;
}

const FCharacterData &ATowerDefenceGameState::AddCharacterData(const FGuid& ID, const FCharacterData& Data)
{
	return GetSaveData()->CharacterData.Add(ID, Data);
}

const FBuildingTower& ATowerDefenceGameState::AddBuildingTower(const FGuid& ID, const FBuildingTower& Data)
{
	return GetSaveData()->BuildingTowers.Add(ID, Data);
}

bool ATowerDefenceGameState::RemoveCharacterData(const FGuid& ID)
{
	return (bool)GetSaveData()->CharacterData.Remove(ID);
}

FCharacterData& ATowerDefenceGameState::GetCharacterData(const FGuid& ID)
{
	
	if (GetSaveData()->CharacterData.Contains(ID))
	{
		return GetSaveData()->CharacterData[ID];
	}

	SD_print(Error, "The current [%s] is invalid", *ID.ToString());

	return CharacterDataNULL;
}

FBuildingTower& ATowerDefenceGameState::GetBuildingTower(const FGuid& ID)
{
	if (GetSaveData()->BuildingTowers.Contains(ID))
	{
		return GetSaveData()->BuildingTowers[ID];
	}

	SD_print(Error, "The current [%s] is invalid", *ID.ToString());

	return BuildingTowerNULL;
}

const TArray<const FGuid*> ATowerDefenceGameState::GetBuildingTowersID()
{
	TArray<const FGuid*> Towers;

	for (const auto &Tmp : GetSaveData()->BuildingTowers)
	{
		Towers.Add(&Tmp.Key);
	}


	return Towers;
}

bool ATowerDefenceGameState::GetTowerDataFormTable(TArray<const FCharacterData*>& Data)
{
	if (!CacheTowerData.Num())
	{
		AITowerCharacterData->GetAllRows(TEXT("Character Data"), CacheTowerData);
	}

	
	for (const auto& Tmp : CacheTowerData)
	{
		Data.Add(Tmp);
	}
	

	return Data.Num() > 0;
}

bool ATowerDefenceGameState::GetMonsterDataFormTable(TArray<const FCharacterData*>& Data)
{
	if (!CacheMonsterData.Num())
	{
		AIMonsterCharacterData->GetAllRows(TEXT("Character Data"), CacheMonsterData);
	}

	for (const auto& Tmp : CacheMonsterData)
	{
		Data.Add(Tmp);
	}


	return Data.Num() > 0;
}

const FCharacterData& ATowerDefenceGameState::GetCharacterDataByID(int32 ID, ECharacterType Type)
{
	TArray<const FCharacterData*> Data;

	switch (Type)
	{
		case ECharacterType::TOWER:
		{
			GetTowerDataFormTable(Data);
			break;
		}
		case ECharacterType::MONSTER:
		{
			GetMonsterDataFormTable(Data);
			break;
		}
	}

	for (const auto& Tmp : Data)
	{
		if (Tmp->ID == ID)
		{
			return *Tmp;
		}
	}


	return CharacterDataNULL;


}

void ATowerDefenceGameState::RequestInventorySlotSwap(const FGuid& A, const FGuid& B)
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

AStaticMeshActor* ATowerDefenceGameState::SpawnTowersDoll(int32 ID)
{
	AStaticMeshActor* OutActor = NULL;
	TArray<const FCharacterData*> InData;
	GetTowerDataFormTable(InData);

	for (const auto& Tmp : InData)
	{
		if (Tmp->ID == ID)
		{

			UClass* NewClass = Tmp->CharacterBlueprintKey.LoadSynchronous();

			if (GetWorld() && NewClass)
			{
				if (ARuleOfTheCharacter* RuleOfTheCharacter = GetWorld()->SpawnActor<ARuleOfTheCharacter>(NewClass, FVector::ZeroVector, FRotator::ZeroRotator))
				{
					if (AStaticMeshActor* MeshActor = GetWorld()->SpawnActor<AStaticMeshActor>(AStaticMeshActor::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator))
					{
						FTransform Transform;
						if (UStaticMesh* InMesh = RuleOfTheCharacter->GetDollMesh(Transform))
						{
							MeshActor->GetStaticMeshComponent()->SetRelativeTransform(Transform);
							MeshActor->SetMobility(EComponentMobility::Movable);
							MeshActor->GetStaticMeshComponent()->SetStaticMesh(InMesh);
							MeshActor->GetStaticMeshComponent()->SetMobility(EComponentMobility::Movable);
							OutActor = MeshActor;
							RuleOfTheCharacter->Destroy();

						}
						else
						{
							MeshActor->Destroy();
							RuleOfTheCharacter->Destroy();
						}
					}
					else
					{
						RuleOfTheCharacter->Destroy();
					}
				}
			}

			break;
		}
	}

	//AStaticMeshActor


	return OutActor;
}

FPlayerData& ATowerDefenceGameState::GetPlayerData()
{
	return GetSaveData()->PlayerData;
}

FGameInstanceData& ATowerDefenceGameState::GetGameData()
{
	return GetSaveData()->GameData;
}

AMonsters* ATowerDefenceGameState::SpawnMonster(int32 CharacterID, int32 CharacterLevel, const FVector& Location, const FRotator& Rotator)
{
	return SpawnCharacter<AMonsters>(CharacterID, CharacterLevel, AIMonsterCharacterData, Location, Rotator);
}

ATowers* ATowerDefenceGameState::SpawnTower(int32 CharacterID, int32 CharacterLevel, const FVector& Location, const FRotator& Rotator)
{
	return SpawnCharacter<ATowers>(CharacterID, CharacterLevel, AITowerCharacterData, Location, Rotator);
}

bool ATowerDefenceGameState::SaveGameData(int32 SaveNumber)
{
	if (SaveData && SlotList)
	{
		SlotList->SlotList.AddGameDataByNumber(SaveNumber);

		return UGameplayStatics::SaveGameToSlot(SlotList, FString::Printf(TEXT("SlotList")), 0)
			&& UGameplayStatics::SaveGameToSlot(SaveData, FString::Printf(TEXT("SaveSlot_%i"),SaveNumber), 0);
	}

	return false;
}

bool ATowerDefenceGameState::ReadGameData(int32 SaveNumber)
{
	SaveData = Cast<UGameSaveData>(UGameplayStatics::LoadGameFromSlot(FString::Printf(TEXT("SaveSlot_%i"), SaveNumber), 0));

	return SaveData != NULL;
}

#if PLATFORM_WINDOWS
#pragma optimize ("" ,on)
#endif