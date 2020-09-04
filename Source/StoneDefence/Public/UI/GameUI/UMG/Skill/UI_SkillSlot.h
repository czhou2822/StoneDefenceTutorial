// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/GameUI/UMG/Core/UI_Slot.h"

#include "UI_SkillSlot.generated.h"

/**
 * 
 */
UCLASS()
class STONEDEFENCE_API UUI_SkillSlot : public UUI_Slot
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	class UImage* SkillIcon;

	UPROPERTY(meta = (BindWidget))
	class UImage* SkillIconCD;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* SkillNumber;

	UPROPERTY(meta = (BindWidget))
	class UTextblock* KeyValueNumber;

	UPROPERTY(meta = (BindWidget))
	class UTextblock* SkillCDValue;

	//UPROPERTY(meta = (BindWidget))
	//class UButton* ClickButton;

public:
	virtual void NativeConstruct();


	void OnClickedWidget();
};
