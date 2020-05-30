// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Core/UI_RuleOfTheWidget.h"
#include "UI_ToolBarSystem.generated.h"

/**
 * 
 */

class UTextBlock;
class UProgressBar;

UCLASS()
class STONEDEFENCE_API UUI_ToolBarSystem : public UUI_RuleOfTheWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	UTextBlock* GameGold;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TowerDeathNumber;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* GameCount;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* KillSoldier;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* GameLevelSurplusQuantity;
	UPROPERTY(meta = (BindWidget))
	UProgressBar* GSQProgressBar;

private:
	FString GetCurrentCount(float NewTimeCount);

public: 
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
};
