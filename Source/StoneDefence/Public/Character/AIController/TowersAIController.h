// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Core/RuleOfTheAIController.h"
#include "TowersAIController.generated.h"

class ARuleOfTheCharacter;

/**
 * 
 */
UCLASS()
class STONEDEFENCE_API ATowersAIController : public ARuleOfTheAIController
{
	GENERATED_BODY()
	

protected:

	UPROPERTY(BlueprintReadWrite)
	TArray<class ARuleOfTheCharacter*> TArrayMonsters;

	//TWeakObjectPtr<class ARuleOfTheCharacter> Target;

	float HeartbeatDiagnosis;

protected:
	
	void BTService_FindTarget();

	virtual void AttackTarget(ARuleOfTheCharacter* AttackTarget);


public:
	ATowersAIController();

	virtual AActor* FindTarget();

	virtual void Tick(float DeltaTime) override;


};
