// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleTutorial/Public/UI_TutorialSystem.h"
#include "MediaAssets/Public/MediaPlayer.h"
#include "Tutorial/UI_TutorialSlot.h"
#include "components/Image.h"
#include "Components/CheckBox.h"
#include "components/Slider.h"
#include "components/TextBlock.h"
#include "components/ScrollBox.h"
#include "Components/Button.h"
#include "Misc/Paths.h"
#include "HAL/FileManager.h"
#include "MediaPlaylist.h"
#include "GlobalTutorialProxy.h"


void UUI_TutorialSystem::NativeConstruct()
{
	Super::NativeConstruct();

	InitMedia();

	//SimpleTutorialMulticastDelegate.BindUObject(this, &UUI_TutorialSystem::SystemPlay);

	MediaPlayer->OnEndReached.AddDynamic(this, &UUI_TutorialSystem::FinishPlayMovie);


	ReplayButton->OnClicked.AddDynamic(this, &UUI_TutorialSystem::Replay);
	PauseButton->OnClicked.AddDynamic(this, &UUI_TutorialSystem::Pause);

	MovieProgress->OnMouseCaptureBegin.AddDynamic(this, &UUI_TutorialSystem::MouseCaptureBegin);
	MovieProgress->OnMouseCaptureEnd.AddDynamic(this, &UUI_TutorialSystem::MouseCaptureEnd);

	SuspendButton->OnCheckStateChanged.AddDynamic(this, &UUI_TutorialSystem::ClickedCheckBox);
}

void UUI_TutorialSystem::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (MediaPlayer)
	{
		float NewValue = MediaPlayer->GetTime().GetTotalSeconds() / MediaPlayer->GetDuration().GetTotalSeconds();
		MovieProgress->SetValue(NewValue);
		PlayTimeText->SetText(FText::FromString(MediaPlayer->GetTime().ToString() + "/" + MediaPlayer->GetDuration().ToString()));
	}
}

void UUI_TutorialSystem::InitMedia()
{
	if (MediaPlayer)
	{
		TArray<FString> MediaFilenames;

		FString MediaPath = FPaths::ConvertRelativePathToFull(FPaths::ProjectDir() / TEXT("Media/"));
		IFileManager::Get().FindFiles(MediaFilenames, *(MediaPath + TEXT("*")), true, false);

		for (int32 i = 0; i < MediaFilenames.Num(); i++)
		{
			if (UUI_TutorialSlot* TutorialSlot = CreateWidget<UUI_TutorialSlot>(this, TutorialSlotClass, FName(TEXT("TutorialSlot"))))
			{
				TutorialSlot->Index = i;
				MediaPlayer->GetPlaylist()->AddFile(MediaPath);
				ScrollMediaList->AddChild(TutorialSlot);
			}
		}
		if (UMediaSource* Media = MediaPlayer->GetPlaylist()->Get(0))
		{
			MediaPlayer->OpenSource(Media);
		}

	}



}

void UUI_TutorialSystem::ActivationMovie()
{
	if (MediaPlayer->IsPlaying())
	{
		MediaPlayer->Pause();
		PauseImage->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		SuspendButton->SetCheckedState(ECheckBoxState::Unchecked);
	}
	else
	{
		MediaPlayer->Play();
		PauseImage->SetVisibility(ESlateVisibility::Hidden);
		SuspendButton->SetCheckedState(ECheckBoxState::Checked);
	}
	
}

void UUI_TutorialSystem::ClickedCheckBox(bool ClickedWidget)
{
}

void UUI_TutorialSystem::Replay()
{
	if (MediaPlayer->IsReady())
	{
		MediaPlayer->Rewind();
	}
}

bool UUI_TutorialSystem::SystemPlay(int32 InIndex)
{
	if (UMediaSource* Media = MediaPlayer->GetPlaylist()->Get(InIndex))
	{
		return MediaPlayer->OpenSource(Media);
	}
	return false;
}


void UUI_TutorialSystem::Pause()
{
	ActivationMovie();
}

void UUI_TutorialSystem::FinishPlayMovie()
{
	if (MediaPlayer->IsReady())
	{
		MediaPlayer->Close();
	}
}

void UUI_TutorialSystem::MouseCaptureBegin()
{

}

void UUI_TutorialSystem::MouseCaptureEnd()
{

}
