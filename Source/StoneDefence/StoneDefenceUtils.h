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
}

namespace Expression
{
	float GetDamage(IRuleCharacter* Enemy, IRuleCharacter* Owner);
}

namespace MeshUtils
{
	UStaticMesh* SkeletalMeshComponentToStaticMesh(UWorld* World, USkeletalMeshComponent *SkeletalMeshComponent);
}