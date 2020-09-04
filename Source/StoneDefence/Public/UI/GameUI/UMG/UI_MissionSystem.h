// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Core/UI_RuleOfTheWidget.h"
#include "UI/GameUI/UMG/Drop/UI_NativeOnDrop.h"

#include "UI_MissionSystem.generated.h"

/**
 * 
 */

class UTextBlock;
class UButton;

UCLASS()
class STONEDEFENCE_API UUI_MissionSystem : public UUI_NativeOnDrop
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ConditionBase;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ConditionA;

	UPROPERTY(meta = (BindWidget))
    class UTextBlock* ConditionB;

	UPROPERTY(meta = (BindWidget))
	class UButton* ConditionButton;

public:
	virtual void NativeConstruct();

	UFUNCTION()
	void Condition();


	
};
