// Fill out your copyright notice in the Description page of Project Settings.


#include "StoneDefence/Public/Core/GameCore/TowerDefenceGameInstance.h"
#include "SimpleScreenLoading/Public/SimpleScreenLoading.h"

void UTowerDefenceGameInstance::Init()
{
	Super::Init();

	FSimpleScreenLoadingModule &SimpleScreenLoadingModule = FModuleManager::LoadModuleChecked<FSimpleScreenLoadingModule>("SimpleScreenLoading");
	SimpleScreenLoadingModule.SetupScreenLoading();
}