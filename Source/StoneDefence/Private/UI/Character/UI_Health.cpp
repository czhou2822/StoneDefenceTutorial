// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/Character/UI_Health.h"
#include "Components/TextBlock.h"
#include "Components/WrapBox.h"
#include "Components/ProgressBar.h"
#include "UI/GameUI/UMG/Skill/UI_CharacterSkillSlot.h"


void UUI_Health::NativeConstruct()
{
	Super::NativeConstruct();
}


void UUI_Health::SetTitle(const FString& Msg)
{
	Title->SetText(FText::FromString(Msg));
}

void UUI_Health::SetHealth(float HeatlhValue)
{
	Health->SetPercent(HeatlhValue);
}

void UUI_Health::AddSkillSlot(FGuid SkillID)
{
	if (CharacterSkillSlotClass)
	{
		if (UUI_CharacterSkillSlot* SkillSlot = CreateWidget<UUI_CharacterSkillSlot>(GetWorld(), CharacterSkillSlotClass))
		{
			SkillSlot->GUID = SkillID;
			if (SkillSlot->GetSkillData().IsValid())
			{
				UTexture2D* ICONTexture = SkillSlot->GetSkillData().Icon.LoadSynchronous();
				SkillSlot->SetTexture(ICONTexture);
				SkillList->AddChild(SkillSlot);
			}

		}
	}
}

bool UUI_Health::RemoveSkillSlot(FGuid SkillID)
{
	UUI_CharacterSkillSlot* RemoveSkillSlot = nullptr;
	for (UPanelSlot* PanelSlot : SkillList->GetSlots())
	{
		if (UUI_CharacterSkillSlot* SkillSlot = Cast<UUI_CharacterSkillSlot>(PanelSlot->Content))
		{
			if (SkillSlot->GUID == SkillID)
			{
				RemoveSkillSlot = SkillSlot;
				break;
			}
		}
	}
	return SkillList->RemoveChild(RemoveSkillSlot);
}
