// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AIController/MonsterAIController.h"
#include "EngineUtils.h"
#include "stonedefence/StoneDefenceUtils.h"
#include "StoneDefence/StoneDefenceType.h"
#include "Character/CharacterCore/Towers.h"

AActor* AMonsterAIController::FindTarget()
{
	if (!Target.IsValid() || !Target->IsActive())
	{
		TArray<ARuleOfTheCharacter*>TargetMainTowersArray;
		TArray<ARuleOfTheCharacter*>TargetTowersArray;

		for (TActorIterator<ATowers>it(GetWorld(), ATowers::StaticClass()); it; ++it)
		{
			ATowers* TheCharacter = *it;
			if (TheCharacter && TheCharacter->IsActive())
			{
				if (TheCharacter->GetType() == EGameCharacterType::Type::TOWER)
				{
					TargetTowersArray.Add(TheCharacter);
				}
				else if (TheCharacter->GetType() == EGameCharacterType::Type::MAIN_TOWER)
				{
					TargetMainTowersArray.Add(TheCharacter);
				}
			}
		}

		ATowers* MainTowers = Cast<ATowers>(StoneDefenceUtils::FindTargetRecently(TargetMainTowersArray, GetPawn()->GetActorLocation()));
		ATowers* NormalTowers = Cast<ATowers>(StoneDefenceUtils::FindTargetRecently(TargetTowersArray, GetPawn()->GetActorLocation()));

		if (MainTowers)
		{
			return MainTowers;
		}
		return NormalTowers;
	}

	return Target.Get();
	
}

void AMonsterAIController::AttackTarget(ARuleOfTheCharacter* AttackTarget)
{

}