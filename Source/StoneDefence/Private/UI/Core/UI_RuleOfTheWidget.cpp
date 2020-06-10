// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Core/UI_RuleOfTheWidget.h"
#include "Animation/WidgetAnimation.h"


UUI_RuleOfTheWidget::UUI_RuleOfTheWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	GUID = FGuid::NewGuid();
}

UWidgetAnimation* UUI_RuleOfTheWidget::GetNameWidgetAnimation(const FString& WidgetAnimationName) const
{
	return nullptr;
}

ATowerDefenceGameState* UUI_RuleOfTheWidget::GetGameState()
{
	if (GetWorld())
	{
		return GetWorld()->GetGameState<ATowerDefenceGameState>();
	}
	return nullptr;
}

ATowerDefencePlayerState* UUI_RuleOfTheWidget::GetPlayerState()
{
	if (GetPlayerController())
	{
		return GetPlayerController()->GetPlayerState<ATowerDefencePlayerState>();
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
