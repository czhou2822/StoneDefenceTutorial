// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Global/Core/ManageCore.h"
#include "CachePoolManagement.generated.h"

class UStaticMesh;
/**
 * 
 */

USTRUCT()
struct STONEDEFENCE_API FDollMeshPoolManage
{
	GENERATED_USTRUCT_BODY()

	void Constructor();
	void Destructural();

	void Add(int32, UStaticMesh*);
	UStaticMesh* GetStaticMesh(int32);

protected:

	UPROPERTY()
	TMap<int32, TWeakObjectPtr<UStaticMesh>> StaticMeshMapping;

};

