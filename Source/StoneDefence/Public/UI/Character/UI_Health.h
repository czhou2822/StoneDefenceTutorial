// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Core/UI_RuleOfTheWidget.h"
#include "UI_Health.generated.h"

/**
 * 
 */
UCLASS()
class STONEDEFENCE_API UUI_Health : public UUI_RuleOfTheWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Title;
	
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* Health;
	
	UPROPERTY(meta = (BindWidget))
	class UWrapBox* SkillList;

	TSubclassOf<class UUI_CharacterSkillSlot> CharacterSkillSlotClass;

public:
	virtual void NativeConstruct() override;

	void SetTitle(const FString& Msg);
	void SetHealth(float HeatlhValue);


	void AddSkillSlot(FGuid SkillID);
	bool RemoveSkillSlot(FGuid SkillID);


};
