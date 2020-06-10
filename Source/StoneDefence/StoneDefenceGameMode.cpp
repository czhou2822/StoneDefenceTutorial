// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "StoneDefenceGameMode.h"
#include "Core/GameCore/TowerDefenceGameState.h"
#include "Core/GameCore/TowerDefencePlayerController.h"
#include "Core/GameCore/TowerDefenceGameCamera.h"
#include "Core/GameCore/TowerDefencePlayerState.h"
#include "character/Core/RuleOfTheCharacter.h"
#include "character/CharacterCore/Monsters.h"
#include "character/CharacterCore/Towers.h"
#include "Engine/DataTable.h"
#include "StoneDefenceUtils.h"
#include "Items/SpawnPoint.h"
#include "UI/GameUI/Core/RuleofTheHUD.h"




AStoneDefenceGameMode::AStoneDefenceGameMode()
{
	GameStateClass = ATowerDefenceGameState::StaticClass();

	PlayerControllerClass = ATowerDefencePlayerController::StaticClass();

	DefaultPawnClass = ATowerDefenceGameCamera::StaticClass();

	PlayerStateClass = ATowerDefencePlayerState::StaticClass();

	HUDClass = ARuleofTheHUD::StaticClass();

	//UE_LOG(LogTemp, Warning, TEXT("GameMode"));
}

void AStoneDefenceGameMode::BeginPlay()
{
	Super::BeginPlay();
	if (ATowerDefenceGameState* InGameState = GetGameState<ATowerDefenceGameState>())
	{
		InGameState->GetGameData().AssignedMonsterAmount();
	}

	SpawnMainTowerRule();

}

void AStoneDefenceGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (ATowerDefenceGameState* InGameState = GetGameState<ATowerDefenceGameState>())
	{
		for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
		{
			if (APlayerController *MyPlayerController = It->Get())
			{
				if (ATowerDefencePlayerState* InPlayerState = MyPlayerController->GetPlayerState<ATowerDefencePlayerState>())
				{
					InPlayerState->GetPlayerData().GameGoldTime += DeltaSeconds;
					if (InPlayerState->GetPlayerData().IsAllowIncrease())
					{
						InPlayerState->GetPlayerData().GameGoldTime = 0.0f;
						InPlayerState->GetPlayerData().GameGold++;
					}

					if (InGameState->GetGameData().GameCount <= 0.f)
					{
						InGameState->GetGameData().bGameOver = true;
					}
					else
					{
						InGameState->GetGameData().GameCount -= DeltaSeconds;
					}

					int32 TowersNum = 0;

					TArray<ARuleOfTheCharacter*> InTowers;
					StoneDefenceUtils::GetAllActor<ATowers>(GetWorld(), InTowers);

					for (ARuleOfTheCharacter* Tower : InTowers)
					{
						if (Tower->IsActive())
						{
							TowersNum++;
						}
					}
					if (TowersNum == 0)
					{
						InGameState->GetGameData().bGameOver = true;
					}
				}
			}
			
		}


		
	}

	SpawnMonsterRule(DeltaSeconds);
	


}

ARuleOfTheCharacter* AStoneDefenceGameMode::SpawnCharacter(
	int32 CharacterID,
	int32 CharacterLevel,
	UDataTable* InCharacterData,
	const FVector& Location,
	const FRotator& Rotator)
{
	ARuleOfTheCharacter* InCharacter = nullptr;


	if (ATowerDefenceGameState* InGameState = GetGameState<ATowerDefenceGameState>())
	{
		if (InCharacterData)
		{
			TArray<FCharacterData*> Data;
			InCharacterData->GetAllRows(TEXT("Character Data"), Data);
			auto GetCharacterData = [&](int32 ID) -> const FCharacterData*
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

			if (const FCharacterData* NewCharacterData = GetCharacterData(CharacterID))
			{
				UClass* NewClass = NewCharacterData->CharacterBlueprintKey.LoadSynchronous();

				if (GetWorld() && NewClass)
				{
					if (ARuleOfTheCharacter* RuleOfTheCharacter = GetWorld()->SpawnActor<ARuleOfTheCharacter>(NewClass, Location, Rotator))
					{
						FCharacterData &CharacterDataInst = InGameState->AddCharacterData(RuleOfTheCharacter->GUID, *NewCharacterData);

						CharacterDataInst.UpdateHealth();

						if (CharacterLevel > 1)
						{
							for (int32 i = 0; i < CharacterLevel; i++)
							{
								CharacterDataInst.UpdateLevel();
							}
						}


						InCharacter = RuleOfTheCharacter;
					}
				}
			}

		}
	}



	return InCharacter;
}


AMonsters* AStoneDefenceGameMode::SpawnMonster(int32 CharacterID, int32 CharacterLevel, const FVector& Location, const FRotator& Rotator)
{
	return SpawnCharacter<AMonsters>(CharacterID, CharacterLevel, GetGameState<ATowerDefenceGameState>()->AIMonsterCharacterData, Location, Rotator);
}

ATowers* AStoneDefenceGameMode::SpawnTower(int32 CharacterID, int32 CharacterLevel, const FVector& Location, const FRotator& Rotator)
{
	return SpawnCharacter<ATowers>(CharacterID, CharacterLevel, GetGameState<ATowerDefenceGameState>()->AITowerCharacterData, Location, Rotator);
}

int32 GetMonsterLevel(UWorld* InWorld)
{
	struct FDifficultyDetermination
	{
		FDifficultyDetermination()
			:Level(0.f)
			, Combination(0.f)
			, Attack(0.f)
			, Defense(0.f)
			, Variance(0.f)
		{

		}
		float Level;
		float Combination;
		float Attack;
		float Defense;
		float Variance;

	};


	auto GetDifficultyDetermination = [](TArray<ARuleOfTheCharacter*>& RuleOfTheCharacter) -> FDifficultyDetermination
	{
		int32 Index = 0;

		FDifficultyDetermination DifficultyDetermination;

		for (ARuleOfTheCharacter* Tmp : RuleOfTheCharacter)
		{
			if (Tmp->IsActive())
			{
				DifficultyDetermination.Level += (float)Tmp->GetCharacterData().Lv;
				DifficultyDetermination.Attack += Tmp->GetCharacterData().PhysicalAttack;
				DifficultyDetermination.Defense += Tmp->GetCharacterData().Armor;
				Index++;
			}
		}

		DifficultyDetermination.Level /= Index;
		DifficultyDetermination.Attack /= Index;
		DifficultyDetermination.Defense /= Index;

		for (ARuleOfTheCharacter* Tmp : RuleOfTheCharacter)
		{
			if (Tmp->IsActive())
			{
				float InValue = (float)Tmp->GetCharacterData().Lv - DifficultyDetermination.Level;
				DifficultyDetermination.Variance += InValue * InValue;
			}
		}

		DifficultyDetermination.Variance /= Index;

		return DifficultyDetermination;
	};


	TArray<ARuleOfTheCharacter*> Towers;
	TArray<ARuleOfTheCharacter*> Monsters;
	StoneDefenceUtils::GetAllActor<AMonsters>(InWorld, Monsters);
	StoneDefenceUtils::GetAllActor<ATowers>(InWorld, Towers);

	FDifficultyDetermination TowerDD = GetDifficultyDetermination(Towers);
	FDifficultyDetermination MonsterDD = GetDifficultyDetermination(Monsters);

	int32 ReturnLevel = TowerDD.Level;

	if (TowerDD.Attack > MonsterDD.Attack)
	{
		ReturnLevel++;
	}
	if (TowerDD.Defense > MonsterDD.Defense)
	{
		ReturnLevel++;
	}

	//ReturnLevel += FMath::Abs(2 - FMath::Sqrt(TowerDD.Variance/10.f));



	return ReturnLevel;


}

void AStoneDefenceGameMode::SpawnMonsterRule(float DeltaSeconds)
{
	if (ATowerDefenceGameState* InGameState = GetGameState<ATowerDefenceGameState>())
	{
		if (!InGameState->GetGameData().bCurrentLevelMissionSuccess)
		{
			if (!InGameState->GetGameData().bGameOver)
			{
				if (InGameState->GetGameData().PerNumberOfMonsters.Num())
				{
					InGameState->GetGameData().CurrentSpawnMonsterTime += DeltaSeconds;
					if (InGameState->GetGameData().IsAllowSpawnMonster())
					{
						InGameState->GetGameData().ResetSpawnMonsterTime();

						int32 MonsterLevel = GetMonsterLevel(GetWorld());
						if (ARuleOfTheCharacter* MyMonster = SpawnMonster(0, MonsterLevel, FVector::ZeroVector, FRotator::ZeroRotator))
						{
							TArray<ASpawnPoint*> MonsterSpawnPoints;

							for (ASpawnPoint* TargetPoint : StoneDefenceUtils::GetAllActor<ASpawnPoint>(GetWorld()))
							{
								if (MyMonster->GetTeamType() == TargetPoint->Team)
								{
									MonsterSpawnPoints.Add(TargetPoint);
									break;
								}
							}
							ASpawnPoint* TargetPoint = MonsterSpawnPoints[FMath::RandRange(0, MonsterSpawnPoints.Num() - 1)];
							MyMonster->SetActorLocation(TargetPoint->GetActorLocation());
							MyMonster->SetActorRotation(TargetPoint->GetActorRotation());

							InGameState->GetGameData().StageDecision();
						}
					}
				}
			}
		}
		else
		{

		}
	}

}

void AStoneDefenceGameMode::SpawnMainTowerRule()
{
	for (ASpawnPoint* TargetPoint : StoneDefenceUtils::GetAllActor<ASpawnPoint>(GetWorld()))
	{
		if (TargetPoint->Team == ETeam::RED)
		{
			SpawnTower(0, 1, TargetPoint->GetActorLocation(), TargetPoint->GetActorRotation());
		}
	}

}

