// Fill out your copyright notice in the Description page of Project Settings.

#include "SimpleGameSettings/Public/UI_GameSettingsSystem.h"
#include "Components/CheckBox.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "SimpleGameSettings/Public/Core/SimpleGameUserSettings.h"
#include "SimpleGameSettings/Public/GameSettings/UI_GameSettingsGame.h"
#include "SimpleGameSettings/Public/GameSettings/UI_GameSettingsAudio.h"
#include "SimpleGameSettings/Public/GameSettings/UI_GameSettingsVideo.h"

void UUI_GameSettingsSystem::NativeConstruct()
{
	Super::NativeConstruct();

	AudioSettingBox->OnCheckStateChanged.AddDynamic(this, &UUI_GameSettingsSystem::AudioSettingCheckBox);
	VideoSettingBox->OnCheckStateChanged.AddDynamic(this, &UUI_GameSettingsSystem::VideoSettingCheckBox);
	GameSettingBox->OnCheckStateChanged.AddDynamic(this, &UUI_GameSettingsSystem::GameSettingCheckBox);

	SaveButton->OnClicked.AddDynamic(this, &UUI_GameSettingsSystem::SaveSettings);
	RestoreDefaultButton->OnClicked.AddDynamic(this, &UUI_GameSettingsSystem::RestoreDefautSettings);

	//¶ÁÈ¡ÓÎÏ·ÉèÖÃ
	LoadSettings();


}

void UUI_GameSettingsSystem::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UUI_GameSettingsSystem::AudioSettingCheckBox(bool ClickedWidget)
{
	SetSettingState(EGameSettingsType::AUDIO);
}

void UUI_GameSettingsSystem::VideoSettingCheckBox(bool ClickedWidget)
{
	SetSettingState(EGameSettingsType::VIDEO);

}

void UUI_GameSettingsSystem::GameSettingCheckBox(bool ClickedWidget)
{
	SetSettingState(EGameSettingsType::GAME);

}

void UUI_GameSettingsSystem::SaveSettings()
{
	GameSettingsVideo->SaveSettings();
	GameSettingsAudio->SaveSettings();
	GameSettingsGameSetting->SaveSettings();

	USimpleGameUserSettings::GetSimpleGameUserSettings()->ApplySettings(true);

	GameSettingsVideo->LoadSettings();
	GameSettingsAudio->LoadSettings();
	GameSettingsGameSetting->LoadSettings();
}

void UUI_GameSettingsSystem::LoadSettings()
{
	USimpleGameUserSettings::GetSimpleGameUserSettings()->LoadSettings(true);

	GameSettingsVideo->LoadSettings();
	GameSettingsAudio->LoadSettings();
	GameSettingsGameSetting->LoadSettings();


}

void UUI_GameSettingsSystem::RestoreDefautSettings()
{
	USimpleGameUserSettings::GetSimpleGameUserSettings()->SetToDefaults();

	LoadSettings();
}


void UUI_GameSettingsSystem::SetSettingState(EGameSettingsType Type)
{
	switch (Type)
	{
	case EGameSettingsType::VIDEO:
		AudioSettingBox->SetCheckedState(ECheckBoxState::Unchecked);
		VideoSettingBox->SetCheckedState(ECheckBoxState::Checked);
		GameSettingBox->SetCheckedState(ECheckBoxState::Unchecked);
		break;
	case EGameSettingsType::AUDIO:
		AudioSettingBox->SetCheckedState(ECheckBoxState::Checked);
		VideoSettingBox->SetCheckedState(ECheckBoxState::Unchecked);
		GameSettingBox->SetCheckedState(ECheckBoxState::Unchecked);
		break;
	case EGameSettingsType::GAME:
		AudioSettingBox->SetCheckedState(ECheckBoxState::Unchecked);
		VideoSettingBox->SetCheckedState(ECheckBoxState::Unchecked);
		GameSettingBox->SetCheckedState(ECheckBoxState::Checked);
		break;
	default:
		break;
	}

	SettingListSwitcher->SetActiveWidgetIndex((int32)Type);


}
