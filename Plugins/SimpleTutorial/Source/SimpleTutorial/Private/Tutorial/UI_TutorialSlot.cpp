// Fill out your copyright notice in the Description page of Project Settings.

#include "components/Button.h"
#include "UI_TutorialSystem.h"
#include "GlobalTutorialProxy.h"
#include "Tutorial/UI_TutorialSlot.h"

UUI_TutorialSlot::UUI_TutorialSlot(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	Index = INDEX_NONE;

}



bool UUI_TutorialSlot::IsIndexValid()
{
	return Index != INDEX_NONE;
}

void UUI_TutorialSlot::SlotPlay()
{
	//if (SimpleTutorialMulticastDelegate.IsBound())
	//{
	//	if (SimpleTutorialMulticastDelegate.Execute(Index))
	//	{

	//	}
	//}
}

void UUI_TutorialSlot::NativeConstruct()
{
	Super::NativeConstruct();
	PlayButton->OnClicked.AddDynamic(this, &UUI_TutorialSlot::SlotPlay);
}