// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskAttackTarget.generated.h"

/**
 * 
 */
UCLASS()
class STONEDEFENCE_API UBTTaskAttackTarget : public UBTTaskNode
{
	GENERATED_BODY()


public:


	UPROPERTY(EditAnywhere, Category = Blackboard)
	struct FBlackboardKeySelector Blackboard_Actor;


public:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;

	virtual void OnGameplayTaskInitialized(UGameplayTask& Task) {};

	virtual void OnGameplayTaskActivated(UGameplayTask& Task) {};

	virtual void OnGameplayTaskDeactivated(UGameplayTask& Task) {};
};
