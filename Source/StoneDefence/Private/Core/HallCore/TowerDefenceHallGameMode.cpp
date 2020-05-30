// Fill out your copyright notice in the Description page of Project Settings.


#include "StoneDefence/Public/Core/HallCore/TowerDefenceHallGameMode.h"
#include "StoneDefence/Public/UI/HallUI/Core/TowerDefenceHallHUD.h"
#include "StoneDefence/Public/Core/HallCore/TowerDefenceHallPawn.h"
#include "StoneDefence/Public/Core/HallCore/TowerDefenceHallPlayerController.h"



ATowerDefenceHallGameMode::ATowerDefenceHallGameMode()
{
	HUDClass = ATowerDefenceHallHUD::StaticClass();
	DefaultPawnClass = ATowerDefenceHallPawn::StaticClass();
	PlayerControllerClass = ATowerDefenceHallPlayerController::StaticClass();
}