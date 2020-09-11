// Fill out your copyright notice in the Description page of Project Settings.


#include "Global/CachePoolManagement.h"
#include "Engine/StaticMesh.h"



void FDollMeshPoolManage::Constructor()
{
}

void FDollMeshPoolManage::Destructural()
{

}

void FDollMeshPoolManage::Add(int32 MeshID, UStaticMesh* NewMesh)
{
	if (StaticMeshMapping.Contains(MeshID))
	{
		StaticMeshMapping[MeshID] = NewMesh;
	}
	else
	{
		StaticMeshMapping.Add(MeshID, NewMesh);
	}
}

UStaticMesh* FDollMeshPoolManage::GetStaticMesh(int32 MeshID)
{
	if (StaticMeshMapping.Contains(MeshID))
	{
		return StaticMeshMapping[MeshID].Get();
	}

	return nullptr;
}