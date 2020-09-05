// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/GameUI/UMG/Core/UI_Slot.h"
#include "UI/Core/UI_RuleOfTheWidget.h"
#include "UI_SkillSlot.generated.h"

/**
 * 
 */
UCLASS()
class STONEDEFENCE_API UUI_SkillSlot : public UUI_Slot
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Number;

public:
	virtual void NativeConstruct();

	virtual void OnClickedWidget();

	void UpdateUI();

	FPlayerSkillData* GetPlayerSkillData();

	FORCEINLINE int32 GeyKeyNumber() const { return KeyNumber; }

private:
	int32 KeyNumber;
};
