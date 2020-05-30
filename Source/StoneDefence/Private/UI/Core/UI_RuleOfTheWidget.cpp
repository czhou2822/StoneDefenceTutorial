// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Core/UI_RuleOfTheWidget.h"
#include "Core/GameCore/TowerDefencePlayerController.h"
#include "Core/GameCore/TowerDefenceGameState.h"


UUI_RuleOfTheWidget::UUI_RuleOfTheWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	GUID = FGuid::NewGuid();
}

ATowerDefenceGameState* UUI_RuleOfTheWidget::GetGameState()
{
	if (GetWorld())
	{
		return GetWorld()->GetGameState<ATowerDefenceGameState>();
	}
	return nullptr;
}

ATowerDefencePlayerController* UUI_RuleOfTheWidget::GetPlayerController()
{
	if (GetWorld())
	{
		return GetWorld()->GetFirstPlayerController<ATowerDefencePlayerController>();
	}
	return nullptr;
}
