// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "core/GameCore/TowerDefencePlayerController.h"
#include "core/GameCore/TowerDefencePlayerState.h"
#include "core/GameCore/TowerDefenceGameState.h"
#include "UI_RuleOfTheWidget.generated.h"

/**
 * 
 */
UCLASS()
class STONEDEFENCE_API UUI_RuleOfTheWidget : public UUserWidget
{
	GENERATED_BODY()


public:
	UUI_RuleOfTheWidget(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UI)
	FGuid GUID;

	UWidgetAnimation* GetNameWidgetAnimation(const FString& WidgetAnimationName) const;
	
	ATowerDefenceGameState* GetGameState();

	ATowerDefencePlayerState* GetPlayerState();

	ATowerDefencePlayerController* GetPlayerController();



};
