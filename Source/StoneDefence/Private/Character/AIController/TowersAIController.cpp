// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/AIController/TowersAIController.h"
#include "StoneDefence/StoneDefenceUtils.h"
#include "Character/CharacterCore/Monsters.h"
#include "Character/CharacterCore/Towers.h"
#include "EngineUtils.h"


ATowersAIController::ATowersAIController()
	:HeartbeatDiagnosis(0.0f)
{
	
}


void ATowersAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	HeartbeatDiagnosis += DeltaTime;
	if (HeartbeatDiagnosis >= 0.5f)
	{
		BTService_FindTarget();
		HeartbeatDiagnosis = 0;
	}

	if (TArrayMonsters.Num())
	{
		if (ATowers* Towers = GetPawn<ATowers>())
		{
			if (!Target.IsValid() || !Target->IsActive())
			{
				Target = Cast<ARuleOfTheCharacter>(FindTarget());
			}
			if (Target.IsValid())
			{
				
				Towers->TowerRotator = FRotationMatrix::MakeFromX(Target->GetActorLocation() - GetPawn()->GetActorLocation()).Rotator();

				if (GetPawn()->GetActorRotation() != FRotator::ZeroRotator)
				{
					Towers->TowerRotator -= GetPawn()->GetActorRotation();
				}


			}
		}
	}


}

AActor* ATowersAIController::FindTarget()
{
	if (TArrayMonsters.Num())
	{
		return StoneDefenceUtils::FindTargetRecently(TArrayMonsters, GetPawn()->GetActorLocation());
	}

	return nullptr;
}



void ATowersAIController::BTService_FindTarget()
{
	TArrayMonsters.Empty();

	if (ATowers* Towers = GetPawn<ATowers>())
	{
		if (Towers->IsActive())
		{
			for (TActorIterator<AMonsters>it(GetWorld(), AMonsters::StaticClass()); it; ++it)
			{
				if (AMonsters* TheCharacter = *it)
				{
					if (TheCharacter->IsActive())
					{
						FVector TDistance = TheCharacter->GetActorLocation() - GetPawn()->GetActorLocation();
						if (TDistance.Size() <= 1600)
						{
							TArrayMonsters.Add(TheCharacter);
						}
					}
				}
			}

			AttackTarget(Target.Get());
		}
	}
}


void ATowersAIController::AttackTarget(ARuleOfTheCharacter* AttackTarget)
{
	if (ATowers* Towers = GetPawn<ATowers>())
	{
		if (TArrayMonsters.Num() > 0)
		{
			Towers->AttackBegin();
			Towers->bAttack = true;
		}
		else
		{
			Towers->AttackEnd();
			Towers->bAttack = false;
		}
	}

}