// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "RuleOfTheAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class STONEDEFENCE_API URuleOfTheAnimInstance : public UAnimInstance
{
	GENERATED_BODY()


private:
	float CurrentTime;

	bool bDelayTime;


public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimAttribute")
	bool bDeath;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimAttribute")
	bool bAttack;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AnimAttribute")
	float Speed;

protected:
	bool IsDelayUpdate(float DeltaSeconds);

public:

	URuleOfTheAnimInstance();

	virtual void NativeInitializeAnimation();

	virtual void NativeUpdateAnimation(float DeltaSeconds);


	
	
};
