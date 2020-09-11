// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h" 
#include "SimpleGameSettingsType.h"
#include "SimpleGameSettings/Public/Core/UI_SimpleGameSettingsCore.h"
#include "UI_GameSettingsSystem.generated.h"


class UCheckBox;
class UButton;
class UWidgetSwitcher;
class UUI_GameSettingsVideo;
class UUI_GameSettingsAudio;
class UUI_GameSettingsGame;
/**
 * 
 */
UCLASS()
class SIMPLEGAMESETTINGS_API UUI_GameSettingsSystem : public UUI_SimpleGameSettingsCore
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	UCheckBox* AudioSettingBox;

	UPROPERTY(meta = (BindWidget))
	UCheckBox* VideoSettingBox;

	UPROPERTY(meta = (BindWidget))
	UCheckBox* GameSettingBox;

	UPROPERTY(meta = (BindWidget))
	UButton* SaveButton;

	UPROPERTY(meta = (BindWidget))
	UButton* RestoreDefaultButton;

	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* SettingListSwitcher;

	UPROPERTY(meta = (BindWidget))
	UUI_GameSettingsVideo* GameSettingsVideo;

	UPROPERTY(meta = (BindWidget))
	UUI_GameSettingsAudio* GameSettingsAudio;

	UPROPERTY(meta = (BindWidget))
	UUI_GameSettingsGame* GameSettingsGameSetting;



public:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION()
	void AudioSettingCheckBox(bool ClickedWidget);

	UFUNCTION()
	void VideoSettingCheckBox(bool ClickedWidget);

	UFUNCTION()
	void GameSettingCheckBox(bool ClickedWidget);

	
	virtual void SaveSettings();

	virtual void LoadSettings();

	UFUNCTION()
	void RestoreDefautSettings();


private:

	void SetSettingState(EGameSettingsType Type);

};
