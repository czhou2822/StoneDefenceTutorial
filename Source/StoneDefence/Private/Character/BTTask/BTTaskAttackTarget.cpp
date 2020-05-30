// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/BTTask/BTTaskAttackTarget.h"
#include "Character/Core/RuleOfTheCharacter.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "Character/AIController/MonsterAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTaskAttackTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);


	if (AMonsterAIController* MyAIController = Cast<AMonsterAIController>(OwnerComp.GetOwner()))
	{
		if (UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent())
		{
			if (Blackboard_Actor.SelectedKeyType == UBlackboardKeyType_Object::StaticClass())
			{
				if (ARuleOfTheCharacter* MyPawn = Cast<ARuleOfTheCharacter>(MyAIController->GetPawn()))
				{
					if (ARuleOfTheCharacter* TargetTower = Cast<ARuleOfTheCharacter>(MyBlackboard->GetValueAsObject(Blackboard_Actor.SelectedKeyName)))
					{
						MyPawn->bAttack = true;
						MyAIController->AttackTarget(TargetTower);
						return EBTNodeResult::Succeeded;
					}
					else
					{
						MyPawn->bAttack = false;
						return EBTNodeResult::Succeeded;
					}
				}
			}
		}
	}
	
	return EBTNodeResult::Failed;

}

void UBTTaskAttackTarget::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);
	
	if (UBlackboardData* BBAsset = GetBlackboardAsset())
	{
		Blackboard_Actor.ResolveSelectedKey(*BBAsset);
	}
	else
	{
		UE_LOG(LogBehaviorTree, Warning, TEXT("Cant initialize task %s"), *GetName());
	}

}
