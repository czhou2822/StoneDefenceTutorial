// Fill out your copyright notice in the Description page of Project Settings.

#include "SimpleGameSettings/Public/GameSettings/UI_GameSettingsVideo.h"
#include "Blueprint/UserWidget.h" 
#include "Components/ComboBoxString.h"
#include "Components/CheckBox.h"
#include "SimpleGameSettings/Public/Core/SimpleGameUserSettings.h"


void UUI_GameSettingsVideo::NativeConstruct()
{
	Super::NativeConstruct();

	FullScreenCheckBox->OnCheckStateChanged.AddDynamic(this, &UUI_GameSettingsVideo::FullScreenCheckClickedBox);
	WindowScreenCheckBox->OnCheckStateChanged.AddDynamic(this, &UUI_GameSettingsVideo::WindowScreenCheckClickedBox);
	SupportPhysXCheckBox->OnCheckStateChanged.AddDynamic(this, &UUI_GameSettingsVideo::SupportPhysXCheckClickedBox);

	BindChangedValue(AntiAliasingSlider);
	BindChangedValue(ShadowQualitySlider);
	BindChangedValue(TextureQualitySlider);
	BindChangedValue(PostProcessingSlider);
	BindChangedValue(EffectsSlider);
	BindChangedValue(FoliageSlider);
	BindChangedValue(ViewDistanceSlider);
	BindChangedValue(OverallScalabilityLevelSlider);

	BindSelectionChanged(ResolutionBoxString);
	BindSelectionChanged(LanguageString);



}

void UUI_GameSettingsVideo::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

void UUI_GameSettingsVideo::SaveSettings()
{
	SetSettingsLevel(TextureQualitySlider,
		[](int32 InLevel)
		{
			USimpleGameUserSettings::GetSimpleGameUserSettings()->SetTextureQuality(InLevel);
		});

	SetSettingsLevel(ShadowQualitySlider,
		[](int32 InLevel)
		{
			USimpleGameUserSettings::GetSimpleGameUserSettings()->SetShadowQuality(InLevel);
		});

	SetSettingsLevel(AntiAliasingSlider,
		[](int32 InLevel)
		{
			USimpleGameUserSettings::GetSimpleGameUserSettings()->SetAntiAliasingQuality(InLevel);
		});

	SetSettingsLevel(PostProcessingSlider,
		[](int32 InLevel)
		{
			USimpleGameUserSettings::GetSimpleGameUserSettings()->SetPostProcessingQuality(InLevel);
		});

	SetSettingsLevel(EffectsSlider,
		[](int32 InLevel)
		{
			USimpleGameUserSettings::GetSimpleGameUserSettings()->SetVisualEffectQuality(InLevel );
		});

	SetSettingsLevel(FoliageSlider,
		[](int32 InLevel)
		{
			USimpleGameUserSettings::GetSimpleGameUserSettings()->SetFoliageQuality(InLevel);
		});

	SetSettingsLevel(ViewDistanceSlider,
		[](int32 InLevel)
		{
			USimpleGameUserSettings::GetSimpleGameUserSettings()->SetViewDistanceQuality(InLevel);
		});	

	SetSettingsLevel(OverallScalabilityLevelSlider,
		[](int32 InLevel)
		{
			if (InLevel != USimpleGameUserSettings::GetSimpleGameUserSettings()->GetOverallScalabilityLevel())
			{
				USimpleGameUserSettings::GetSimpleGameUserSettings()->SetOverallScalabilityLevel(InLevel);
			}
		});

}

void UUI_GameSettingsVideo::LoadSettings()
{
	LoadSettingsLevel(AntiAliasingSlider,
		[]()
		{
			return USimpleGameUserSettings::GetSimpleGameUserSettings()->GetAntiAliasingQuality();
		});

	LoadSettingsLevel(TextureQualitySlider,
		[]()
		{
			return USimpleGameUserSettings::GetSimpleGameUserSettings()->GetTextureQuality();
		});

	LoadSettingsLevel(ShadowQualitySlider,
		[]()
		{
			return USimpleGameUserSettings::GetSimpleGameUserSettings()->GetShadowQuality();
		});

	LoadSettingsLevel(PostProcessingSlider,
		[]()
		{
			return USimpleGameUserSettings::GetSimpleGameUserSettings()->GetPostProcessingQuality();
		});

	LoadSettingsLevel(EffectsSlider,
		[]()
		{
			return USimpleGameUserSettings::GetSimpleGameUserSettings()->GetVisualEffectQuality();
		});

	LoadSettingsLevel(ViewDistanceSlider,
		[]()
		{
			return USimpleGameUserSettings::GetSimpleGameUserSettings()->GetViewDistanceQuality();
		});

	LoadSettingsLevel(FoliageSlider,
		[]()
		{
			return USimpleGameUserSettings::GetSimpleGameUserSettings()->GetFoliageQuality();
		});

	LoadSettingsLevel(OverallScalabilityLevelSlider,
		[]()
		{
			return USimpleGameUserSettings::GetSimpleGameUserSettings()->GetOverallScalabilityLevel();
		});


	LoadBoxString(ResolutionBoxString,
		[]()
		{
			FIntPoint ResolutionPoint = USimpleGameUserSettings::GetSimpleGameUserSettings()->GetScreenResolution();
			return FString::Printf(TEXT("%ix%i"), ResolutionPoint.X, ResolutionPoint.Y);
		});


	LoadBoxString(LanguageString,
		[]()
		{
			return USimpleGameUserSettings::GetSimpleGameUserSettings()->GetCurrentLanguageType();
		});


	EWindowMode::Type InModeType = USimpleGameUserSettings::GetSimpleGameUserSettings()->GetFullscreenMode();


	switch (InModeType)
	{
	case EWindowMode::WindowedFullscreen:
	case EWindowMode::Fullscreen:
		FullScreenCheckBox->SetCheckedState(ECheckBoxState::Checked);
		WindowScreenCheckBox->SetCheckedState(ECheckBoxState::Unchecked);
		break;
	case EWindowMode::Windowed:
		FullScreenCheckBox->SetCheckedState(ECheckBoxState::Unchecked);
		WindowScreenCheckBox->SetCheckedState(ECheckBoxState::Checked);
		break;
	case EWindowMode::NumWindowModes:
		break;
	}

}


void UUI_GameSettingsVideo::FullScreenCheckClickedBox(bool ClickedWidget)
{
	FullScreenCheckBox->SetCheckedState(ECheckBoxState::Checked);
	WindowScreenCheckBox->SetCheckedState(ECheckBoxState::Unchecked);
	USimpleGameUserSettings::GetSimpleGameUserSettings()->SetFullscreenMode(EWindowMode::Fullscreen);
}

void UUI_GameSettingsVideo::WindowScreenCheckClickedBox(bool ClickedWidget)
{
	WindowScreenCheckBox->SetCheckedState(ECheckBoxState::Checked);
	FullScreenCheckBox->SetCheckedState(ECheckBoxState::Unchecked);
	USimpleGameUserSettings::GetSimpleGameUserSettings()->SetFullscreenMode(EWindowMode::Windowed);

}

void UUI_GameSettingsVideo::SupportPhysXCheckClickedBox(bool ClickedWidget)
{

}

void UUI_GameSettingsVideo::ChangedValue(float InValue)
{
	UpdateAttribute(AntiAliasingSlider, AntiAliasingText);	//锯齿
	UpdateAttribute(ShadowQualitySlider, ShadowQualityText);//阴影
	UpdateAttribute(TextureQualitySlider, TextureQualityText);//贴图 
	UpdateAttribute(PostProcessingSlider, PostProcessingText);//后期
	UpdateAttribute(EffectsSlider, EffectsText);//特效
	UpdateAttribute(FoliageSlider, FoliageText);//植被
	UpdateAttribute(ViewDistanceSlider, ViewDistanceText);//视距
	UpdateAttribute(OverallScalabilityLevelSlider, OverallScalabilityLevelSliderText);

}

void UUI_GameSettingsVideo::SelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	//更新语言
	{
		FString LanguageTmp = LanguageString->GetSelectedOption();
		USimpleGameUserSettings::GetSimpleGameUserSettings()->SetCurrentLanguage(LanguageTmp);
	}


	//更新分辨率
	{
		FIntPoint ResolutionPoint;
		FString ResolutionTemp = ResolutionBoxString->GetSelectedOption();

		FString R, L;
		ResolutionTemp.Split(TEXT("x"), &R, &L);

		ResolutionPoint.X = FCString::Atoi(*R);
		ResolutionPoint.Y = FCString::Atoi(*L);

		USimpleGameUserSettings::GetSimpleGameUserSettings()->SetScreenResolution(ResolutionPoint);
	}


}
