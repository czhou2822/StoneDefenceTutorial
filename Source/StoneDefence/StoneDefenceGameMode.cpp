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
		StoneDefenceUtils::CallUpdateAllClient(GetWorld(), [&](ATowerDefencePlayerController* MyPlayerController)
			{
				if (ATowerDefencePlayerState* InPlayerState = MyPlayerController->GetPlayerState<ATowerDefencePlayerState>())
				{
					InPlayerState->GetPlayerData().GameGoldTime += DeltaSeconds;
					if (InPlayerState->GetPlayerData().IsAllowIncrease())
					{
						InPlayerState->GetPlayerData().GameGoldTime = 0.0f;
						InPlayerState->GetPlayerData().GameGold++;
					}
				}
			}
		);

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

	SpawnMonsterRule(DeltaSeconds);
	
	//update skill
	UpdateSkill(DeltaSeconds);


}

void AStoneDefenceGameMode::UpdateSkill(float DeltaSeconds)
{
	if (ATowerDefenceGameState* InGameState = GetGameState<ATowerDefenceGameState>())
	{
		////get team member in range
		//auto GetTeam = [&](TArray<FCharacterData*>& TeamArray,const TPair<FGuid, FCharacterData> &Owner, bool bReversed = false)
		//{
		//	auto TeamIner = [](TArray<FCharacterData*>& TeamArray, FCharacterData* CharacterData, const FVector& Loc, float InRange)
		//	{
		//		if (InRange != 0)
		//		{
		//			float Distance = (CharacterData->Location - Loc).Size();
		//			if (Distance <= InRange)
		//			{
		//				TeamArray.Add(CharacterData);
		//			}
		//		}
		//		else
		//		{
		//			TeamArray.Add(CharacterData);
		//		}
		//	};

		//	for (auto& Tmp : InGameState->GetSaveData()->CharacterData)
		//	{
		//		if (bReversed)
		//		{
		//			if (Tmp.Value.Team != Owner.Value.Team)
		//			{
		//				TeamIner(TeamArray, &Tmp.Value, Owner.Value.Location, InRange);
		//			}

		//		}
		//		else
		//		{
		//			if (Tmp.Value.Team == Owner.Value.Team)
		//			{
		//				TeamIner(TeamArray, &Tmp.Value, Owner.Value.Location, InRange);
		//			}
		//		}
		//	}
		//};



		//获取范围 有效友军
		auto GetTeam = [&](TArray<TPair<FGuid, FCharacterData>*> &TeamArray,TPair<FGuid, FCharacterData> &Onwer,float InRange,bool bReversed = false)
		{
			auto TeamIner = [&](TPair<FGuid, FCharacterData> &Target)
			{
				if (InRange != 0)
				{
					float Distance = (Target.Value.Location - Onwer.Value.Location).Size();
					if (Distance <= InRange)
					{
						TeamArray.Add(&Target);
					}
				}
				else
				{
					TeamArray.Add(&Target);
				}
			};

			for (auto &Tmp : InGameState->GetSaveData()->CharacterData)
			{
				if (bReversed)
				{
					if (Tmp.Value.Team == Onwer.Value.Team)
					{
						TeamIner(Tmp);
					}
				}
				else
				{
					if (Tmp.Value.Team != Onwer.Value.Team)
					{
						TeamIner(Tmp);
					}
				}
			}
		};

		//多个角色添加同样技能
		auto AddSkills = [&](TArray<TPair<FGuid, FCharacterData>*> &RecentForces, FSkillData & InSkill)
		{
			for (auto& CharacterElement : RecentForces)
			{
				InGameState->AddSkill(*CharacterElement, InSkill);
			}
		};

		//寻找最近的那个数据目标
		auto FindRangeTargetRecently = [&](const TPair<FGuid, FCharacterData> &InOwner,bool bReversed = false) ->TPair<FGuid, FCharacterData>*
		{
			float TargetDistance = 99999999;
			FGuid Index;

			auto InitTargetRecently = [&](TPair<FGuid, FCharacterData> &Pair)
			{
				FVector Location = Pair.Value.Location;
				FVector TmpVector = Location - InOwner.Value.Location;
				float Distance = TmpVector.Size();

				if (Distance < TargetDistance && Pair.Value.Health > 0)
				{
					Index = Pair.Key;
					TargetDistance = Distance;
				}
			};

			for (auto &Tmp : InGameState->GetSaveData()->CharacterData)
			{
				if (InOwner.Key != Tmp.Key) //ignore self
				{
					if (bReversed)
					{
						//find enemy
						if (InOwner.Value.Team != Tmp.Value.Team)
						{
							InitTargetRecently(Tmp);
						}
					}
					else
					{
						//find friend
						if (InOwner.Value.Team == Tmp.Value.Team)
						{
							InitTargetRecently(Tmp);
						}		
					}	
				}
			}

			if (Index != FGuid())
			{
				for (auto& GameTmp : InGameState->GetSaveData()->CharacterData)
				{
					if (GameTmp.Key == Index)
					{
						return &GameTmp;
					}
				}

				return nullptr;
			}

			return nullptr;
		};

		//获取的模板
		const TArray<FSkillData*>& SkillDataTemplate = InGameState->GetSkillDataFormTable();

		for (auto& Tmp : InGameState->GetSaveData()->CharacterData)
		{
			if (Tmp.Value.Health >0.f)
			{
				//计算和更新
				TArray<FGuid> RemoveSkill;
				for (auto& SkillTmp : Tmp.Value.AdditionalSkillData)
				{
					SkillTmp.Value.SkillDuration += DeltaSeconds;

					if (SkillTmp.Value.SkillType.SkillType == ESkillType::BURST)
					{
						RemoveSkill.Add(SkillTmp.Key);
					}

					//时间到了自然移除
					if (SkillTmp.Value.SkillType.SkillType == ESkillType::SECTION ||
						SkillTmp.Value.SkillType.SkillType == ESkillType::ITERATION)
					{
						if (SkillTmp.Value.SkillDuration <= 0)
						{
							RemoveSkill.Add(SkillTmp.Key);
						}
					}

					//迭代 进行持续更新技能
					if (SkillTmp.Value.SkillType.SkillType == ESkillType::ITERATION)
					{
						SkillTmp.Value.SkillDurationTime += DeltaSeconds;
						if (SkillTmp.Value.SkillDurationTime >= 1.0f)
						{
							SkillTmp.Value.SkillDurationTime = 0.f;

							if (SkillTmp.Value.SkillType.SkillEffectType == ESkillEffectType::ADD)
							{
								Tmp.Value.Health += SkillTmp.Value.Health;
								Tmp.Value.PhysicalAttack += SkillTmp.Value.PhysicalAttack;
								Tmp.Value.Armor += SkillTmp.Value.Armor;
								Tmp.Value.AttackSpeed += SkillTmp.Value.PhysicalAttack;
								Tmp.Value.Gold += SkillTmp.Value.Gold;
							}
							else
							{
								Tmp.Value.Health -= SkillTmp.Value.Health;
								Tmp.Value.PhysicalAttack -= SkillTmp.Value.PhysicalAttack;
								Tmp.Value.Armor -= SkillTmp.Value.Armor;
								Tmp.Value.AttackSpeed -= SkillTmp.Value.PhysicalAttack;
								Tmp.Value.Gold -= SkillTmp.Value.Gold;
							}

							//call客户端 进行特效子弹播放
							StoneDefenceUtils::CallUpdateAllClient(GetWorld(), [&](ATowerDefencePlayerController* MyPlayerController)
							{
								MyPlayerController->SpawnBullet_Client(Tmp.Key, SkillTmp.Value.ID);
							});

						}
					}
				}

				//清理
				for (FGuid& RemoveID : RemoveSkill)
				{
					//tell client to remove skill
					StoneDefenceUtils::CallUpdateAllClient(GetWorld(), [&](ATowerDefencePlayerController* MyPlayerController)
					{
						MyPlayerController->RemoveSkillSlot_Server(Tmp.Key, RemoveID);
					});

					Tmp.Value.AdditionalSkillData.Remove(RemoveID);
				}

				TArray<FSkillData> RemoveSkills;
				//主技能的释放
				for (auto& InSkill : Tmp.Value.CharacterSkill)
				{
					InSkill.CDTime += DeltaSeconds;
					//触发
					if (InSkill.CDTime >= Tmp.Value.CD)
					{
						InSkill.CDTime = 0.0f;

						if (!InSkill.bBecomeEffective)
						{
							if (InSkill.SkillType.SkillAttackType == ESkillAttackType::MULTIPLE)
							{
								//TArray<FCharacterData*>& Recent;
								TArray<TPair<FGuid, FCharacterData>*> Recent;
								if (InSkill.SkillType.SkillTargetType == ESkillTargetType::FRIENDLY_FORCE)
								{
									GetTeam(Recent, Tmp, InSkill.AttackRange);  //get all friendly force
								}
								else if (InSkill.SkillType.SkillTargetType == ESkillTargetType::ENEMY)
								{
									GetTeam(Recent, Tmp, InSkill.AttackRange, true);  //get all friendly force
								}
								if (Recent.Num())
								{
									AddSkills(Recent, InSkill);
								}
							}
							else if (InSkill.SkillType.SkillAttackType == ESkillAttackType::SINGLE)
							{
								TPair<FGuid, FCharacterData>* Recent = nullptr;
								if (InSkill.SkillType.SkillTargetType == ESkillTargetType::FRIENDLY_FORCE)
								{
									Recent = FindRangeTargetRecently(Tmp);
								}

								else if (InSkill.SkillType.SkillTargetType == ESkillTargetType::ENEMY)
								{
									Recent = FindRangeTargetRecently(Tmp, true);
								}

								if (Recent)
								{
									InGameState->AddSkill(*Recent, InSkill);
								}
							}
							InSkill.bBecomeEffective = true;
						}
						else
						{
							RemoveSkills.Add(InSkill);
						}
					}
				}

				for (auto& InSkill : RemoveSkills)
				{
					Tmp.Value.CharacterSkill.Remove(InSkill);

					if(InSkill.SubmissionSkillRequestType == ESubmissionSkillRequestType::AUTO)
					{
						//call客户端 进行特效子弹播放
						StoneDefenceUtils::CallUpdateAllClient(GetWorld(), [&](ATowerDefencePlayerController* MyPlayerController)
						{
							MyPlayerController->SpawnBullet_Client(Tmp.Key, InSkill.ID);
						});
					}
				}
			}
		}
	}
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
						RuleOfTheCharacter->ResetGUID();
						FCharacterData &CharacterDataInst = InGameState->AddCharacterData(RuleOfTheCharacter->GUID, *NewCharacterData);
						CharacterDataInst.UpdateHealth();

						if (CharacterLevel > 1)
						{
							for (int32 i = 0; i < CharacterLevel; i++)
							{
								CharacterDataInst.UpdateLevel();
							}
						}

						//初始化被动技能
						RuleOfTheCharacter->InitSkill();

						//注册队伍
						RuleOfTheCharacter->RegisterTeam();
						
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
				DifficultyDetermination.Attack += Tmp->GetCharacterData().GetAttack();
				DifficultyDetermination.Defense += Tmp->GetCharacterData().GetArmor();
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

