// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Core/UI_RuleOfTheWidget.h"
#include "UI_SkillTip.generated.h"

/**
 * 
 */
UCLASS()
class STONEDEFENCE_API UUI_SkillTip : public UUI_RuleOfTheWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	class URichTextBlock* RichText;

};
