// Fill out your copyright notice in the Description page of Project Settings.


#include "StoneDefence/Public/UI/GameUI/Core/RuleofTheHUD.h"
#include "UObject/ConstructorHelpers.h"
#include "UI/GameUI/UMG/UI_MainScreen.h"

ARuleofTheHUD::ARuleofTheHUD()
{
	static ConstructorHelpers::FClassFinder<UUI_MainScreen> GameMain_BPClass(TEXT("/Game/UI/Game/MainScreen_BP"));
	MainScreenClass = GameMain_BPClass.Class;
}

void ARuleofTheHUD::BeginPlay()
{
	Super::BeginPlay();

	MainScreen = CreateWidget<UUI_MainScreen>(GetWorld(), MainScreenClass);
	MainScreen->AddToViewport();
}
