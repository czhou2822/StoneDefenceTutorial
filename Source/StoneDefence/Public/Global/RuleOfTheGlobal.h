// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Global/GlobalManagement.h"
#include "Global/CachePoolManagement.h"




FManagementCore<FDollMeshPoolManage> GDollMeshPoolManage;
FManagementCore<FGlobalManagement> GManagement;

#define GET_PTR() Get(GetWorld())

#define GLOBAL_MANAGEMENT_MACRO() GManagement.GET_PTR()
#define DOLL_MESH_POOL_MANAGE_MACRO() GDollMeshPoolManage.GET_PTR()
