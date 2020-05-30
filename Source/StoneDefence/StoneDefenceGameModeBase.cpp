// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "StoneDefenceGameModeBase.h"
#include "Core/GameCore/TowerDefenceGameState.h"
#include "Core/GameCore/TowerDefencePlayerController.h"
#include "Core/GameCore/TowerDefenceGameCamera.h"
#include "Core/GameCore/TowerDefencePlayerState.h"
#include "UI/GameUI/Core/RuleofTheHUD.h"


AStoneDefenceGameModeBase::AStoneDefenceGameModeBase()
{
	GameStateClass = ATowerDefenceGameState::StaticClass();

	PlayerControllerClass = ATowerDefencePlayerController::StaticClass();

	DefaultPawnClass = ATowerDefenceGameCamera::StaticClass();

	PlayerStateClass = ATowerDefencePlayerState::StaticClass();

	HUDClass = ARuleofTheHUD::StaticClass();

	//UE_LOG(LogTemp, Warning, TEXT("GameMode"));
}
