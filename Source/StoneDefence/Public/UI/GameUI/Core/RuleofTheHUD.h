// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RuleofTheHUD.generated.h"

class UUI_MainScreen;
class UUI_NativeOnDrop;

UCLASS()
class STONEDEFENCE_API ARuleofTheHUD : public AHUD
{
	GENERATED_BODY()
	
private:
	TSubclassOf<UUI_MainScreen> MainScreenClass;

	TSubclassOf<UUI_NativeOnDrop> NativeOnDropClass;

	UUI_MainScreen* MainScreen;
	UUI_NativeOnDrop* NativeOnDropPtr;

public:

	ARuleofTheHUD();

	virtual void BeginPlay() override;
};
