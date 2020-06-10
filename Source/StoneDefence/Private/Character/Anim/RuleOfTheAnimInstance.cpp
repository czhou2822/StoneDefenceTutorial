// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Anim/RuleOfTheAnimInstance.h"
#include "Character/Core/RuleOfTheCharacter.h"
#include "..\..\..\Public\Character\Anim\RuleOfTheAnimInstance.h"


URuleOfTheAnimInstance::URuleOfTheAnimInstance()
	:bDeath(false)
	, bAttack(false)
	, Speed(0.0f)
	, CurrentTime(0.f)
	, bDelayTime(false)
{

}

void URuleOfTheAnimInstance::NativeInitializeAnimation()
{

}

void URuleOfTheAnimInstance::NativeUpdateAnimation(float Deltaseconds)
{
	if (IsDelayUpdate(Deltaseconds))
	{
		if (ARuleOfTheCharacter* RuleOfTheCharacter = Cast<ARuleOfTheCharacter>(TryGetPawnOwner()))
		{
			bAttack = RuleOfTheCharacter->bAttack;
			Speed = RuleOfTheCharacter->GetVelocity().Size();
			bDeath = !RuleOfTheCharacter->IsActive();
		}
	}
}

bool URuleOfTheAnimInstance::IsDelayUpdate(float Deltaseconds)
{
	if (!bDelayTime)
	{
		CurrentTime += Deltaseconds;
		if (CurrentTime > 0.3f)
		{
			bDelayTime = true;
		}

		return false;
	}

	return true;
}
