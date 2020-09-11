// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SimpleGameSettings/Public/Core/UI_SimpleGameSettingsCore.h"

#include "UI_GameSettingsGame.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLEGAMESETTINGS_API UUI_GameSettingsGame  : public UUI_SimpleGameSettingsCore
{
	GENERATED_BODY()

public:

	virtual void SaveSettings();

	virtual void LoadSettings();


	
};
