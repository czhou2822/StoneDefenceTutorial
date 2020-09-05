// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameUI/UMG/Skill/UI_SkillSlot.h"
#include "Components/Button.h"
#include "Global/UI_Data.h"
#include "Components/TextBlock.h"
#include "Data/PlayerSkillData.h"


void UUI_SkillSlot::NativeConstruct()
{
	Super::NativeConstruct();

	if (PlayerSkillNumber == 9)
	{
		PlayerSkillNumber = 0;
		Number->SetText(FText::FromString(FString::FromInt(PlayerSkillNumber)));
	}
	else
	{
		Number->SetText(FText::FromString(FString::FromInt(++PlayerSkillNumber)));
	}

	KeyNumber = PlayerSkillNumber;

	FString PlayerSkillName = FString::Printf(TEXT("PlayerSkill_%i"), PlayerSkillNumber);
	GetPlayerController()->InputComponent->BindAction(*PlayerSkillName, IE_Pressed, this, &UUI_SkillSlot::OnClickedWidget);
}

void UUI_SkillSlot::OnClickedWidget()
{
	FString PlayerSkillName = FString::Printf(TEXT("PlayerSkill_%i"), PlayerSkillNumber);
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, *PlayerSkillName);

	if (GetPlayerState()->IsVerificationSkill(GUID))
	{
		GetPlayerState()->UsePlayerSkill(GUID);
	}


}

//UpdateSlotInfo(GetPlayerSkillData()->SkillNumber, GetPlayerSkillData()->CDTime);


void UUI_SkillSlot::UpdateUI()
{
	UpdateSlotUI(GetPlayerSkillData()->Icon.LoadSynchronous(),GetPlayerSkillData()->SkillNumber);
}

FPlayerSkillData* UUI_SkillSlot::GetPlayerSkillData()
{
	return GetPlayerState()->GetPlayerSkillData(GUID);
}
