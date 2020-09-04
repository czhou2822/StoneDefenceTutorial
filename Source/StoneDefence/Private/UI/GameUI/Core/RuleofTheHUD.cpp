// Fill out your copyright notice in the Description page of Project Settings.


#include "StoneDefence/Public/UI/GameUI/Core/RuleofTheHUD.h"
#include "UObject/ConstructorHelpers.h"
#include "UI/GameUI/UMG/UI_MainScreen.h"
#include "UI/GameUI/UMG/Drop/UI_NativeOnDrop.h"



ARuleofTheHUD::ARuleofTheHUD()
{
	static ConstructorHelpers::FClassFinder<UUI_MainScreen> GameMain_BPClass(TEXT("/Game/UI/Game/MainScreen_BP"));
	MainScreenClass = GameMain_BPClass.Class;

	static ConstructorHelpers::FClassFinder<UUI_NativeOnDrop> NativeOnDrop_BPClass(TEXT("/Game/UI/Game/Drop/Drop_BP"));
	NativeOnDropClass = NativeOnDrop_BPClass.Class;
}

void ARuleofTheHUD::BeginPlay()
{
	Super::BeginPlay();

	MainScreen = CreateWidget<UUI_MainScreen>(GetWorld(), MainScreenClass);
	MainScreen->AddToPlayerScreen(2);

	NativeOnDropPtr = CreateWidget<UUI_NativeOnDrop>(GetWorld(), NativeOnDropClass);
	NativeOnDropPtr->AddToPlayerScreen(0);
}

void ARuleofTheHUD::UpdateInventorySlot(const FGuid& InventorySlotGUID, bool bInCD)
{
	if (MainScreen)
	{
		MainScreen->UpdateInventorySlot(InventorySlotGUID, bInCD);
	}
}
