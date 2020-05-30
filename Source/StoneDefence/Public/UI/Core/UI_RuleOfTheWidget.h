// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
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
	
	class ATowerDefenceGameState* GetGameState();

	class ATowerDefencePlayerController* GetPlayerController();



};
