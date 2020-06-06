// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/GameUI/UMG/UI_ToolBarSystem.h"
#include "StoneDefence/Public/Core/GameCore/TowerDefenceGameState.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"




void UUI_ToolBarSystem::NativeConstruct()
{
	Super::NativeConstruct();
}

void UUI_ToolBarSystem::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);


	//countdown
	GameCount->SetText(FText::FromString(GetCurrentCount(GetGameState()->GetGameData().GameCount)));
	//player gold count
	GameGold->SetText(FText::AsNumber(GetGameState()->GetPlayerData().GameGold));
	//tower death count
	TowerDeathNumber->SetText(FText::AsNumber(GetGameState()->GetGameData().TowersDeathNumber));
	//kill count
	KillSoldier->SetText(FText::AsNumber(GetGameState()->GetGameData().KillMonstersNumber));
	//monster remaining count
	GSQProgressBar->SetPercent(GetGameState()->GetGameData().GetPerOfRemMonsters());

	GameLevelSurplusQuantity->SetText(FText(
		FText::FromString(FString::Printf(TEXT("%2d/%2d"),
			GetGameState()->GetGameData().PerNumberOfMonsters.Num(),
			GetGameState()->GetGameData().MaxStagesAreMonsters - GetGameState()->GetGameData().PerNumberOfMonsters.Num()))
	));
}


FString UUI_ToolBarSystem::GetCurrentCount(float NewTimeCount)
{

	const int32 NewOurTime = FMath::Max(0, FMath::TruncToInt(NewTimeCount));

	const int32 NewMinutes = NewOurTime / 60;
	const int32 NewSeconds = NewOurTime % 60;
	return FString::Printf(TEXT("%02d:%02d"), NewMinutes, NewSeconds);



}