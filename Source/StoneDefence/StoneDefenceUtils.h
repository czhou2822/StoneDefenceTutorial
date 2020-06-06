// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class ARuleOfTheCharacter;
class IRuleCharacter;
class USkeletalMeshComponent;
class UWorld;

namespace StoneDefenceUtils
{
	ARuleOfTheCharacter* FindTargetRecently(const TArray<ARuleOfTheCharacter*>& InCharacters, const FVector& Loc);

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
			if (Type* A = Cast<Type>(*It))
			{
				Array.Add(A);
			}
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
}

namespace Expression
{
	float GetDamage(IRuleCharacter* Enemy, IRuleCharacter* Owner);
}

namespace MeshUtils
{
	UStaticMesh* SkeletalMeshComponentToStaticMesh(UWorld* World, USkeletalMeshComponent *SkeletalMeshComponent);
}