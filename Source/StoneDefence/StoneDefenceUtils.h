// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Bullet/RuleOfTheBullet.h"
#include "EngineUtils.h"

class ARuleOfTheCharacter;
class IRuleCharacter;
class USkeletalMeshComponent;
class UWorld;
class AStaticMeshActor;
class ATowerDefencePlayerController;

namespace StoneDefenceUtils
{
	void CallUpdateAllClient(UWorld *World, TFunction<void(ATowerDefencePlayerController* MyPlayerController)> InImplement);

	void FindRangeTargetRecently(ARuleOfTheCharacter* InOwner, float Range, TArray<ARuleOfTheCharacter*>& Targets);

	ARuleOfTheCharacter* FindTargetRecently(const TArray<ARuleOfTheCharacter*>& InCharacters, const FVector& Loc);

	ARuleOfTheBullet* SpawnBullet(UWorld* World, FGuid CharacterID, UClass* InClass);

	ARuleOfTheBullet* SpawnBullet(UWorld* World, APawn *NewPawn, UClass *InClass, const FVector &Loc, const FRotator &Rot);

	ARuleOfTheBullet* SpawnBullet(UWorld* World, ARuleOfTheCharacter* Owner, const int32 SkillID, const FVector& Loc, const FRotator& Rot);


	template<class A, class B>
	void GetAllActor(UWorld* World, TArray<B*>& Array)
	{
		for (TActorIterator<A>It(World, A::StaticClass()); It; ++It)
		{
			if (B* Tmp = Cast<A>(*It))
			{
				Array.Add(Tmp);
			}
		}
	}



	template<class Type>
	void GetAllActor(UWorld *World, TArray<Type*> &Array)
	{
		for (TActorIterator<Type>It(World, Type::StaticClass()); It; ++It)
		{
			Array.Add(*It);
		}
	}



	template<class Type>
	TArray<Type*> GetAllActor(UWorld* World)
	{
		TArray<Type*> Array;
		for (TActorIterator<Type>It(World, Type::StaticClass()); It; ++It)
		{
			if (Type* A = Cast<Type>(*It))
			{
				Array.Add(A);
			}
		}
		return Array;
	}


	void Execution(UWorld* World, const FGuid& CharacterID, TFunction<void(ARuleOfTheCharacter* InCharacter)> Code);


	AStaticMeshActor* SpawnTowersDoll(UWorld* World, int32 ID);



}

namespace Expression
{
	float GetDamage(IRuleCharacter* Enemy, IRuleCharacter* Owner);
}

namespace MeshUtils
{

	UStaticMesh* ParticleSystemComponentToStaticMesh(UParticleSystemComponent* NewParticleComponent);
	UStaticMesh* SkeletalMeshComponentToStaticMesh(USkeletalMeshComponent *SkeletalMeshComponent);


}
