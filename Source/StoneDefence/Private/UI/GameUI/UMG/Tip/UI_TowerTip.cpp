// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/GameUI/UMG/Tip/UI_TowerTip.h"
#include "Components/TextBlock.h"
#include "Components/MultiLineEditableTextBox.h"
#include "Data/CharacterData.h"

void UUI_TowerTip::InitTip(const FCharacterData& InData)
{

	CharacterNameBlock->SetText(FText::FromName(InData.Name));
	ConsumeGoldBlock->SetText(FText::AsNumber(InData.Gold));
	CharacterHealthBlock->SetText(FText::AsNumber(InData.MaxHealth));
	CharacterAttackBlock->SetText(FText::AsNumber(InData.PhysicalAttack));
	CharacterArmorBlock->SetText(FText::AsNumber(InData.Armor));
	CharacterAttackSpeedBlock->SetText(FText::AsNumber(InData.AttackSpeed));
	IntroductionBox->SetText(InData.Introduction);
	LVBlock->SetText(FText::AsNumber(InData.Lv));

}
