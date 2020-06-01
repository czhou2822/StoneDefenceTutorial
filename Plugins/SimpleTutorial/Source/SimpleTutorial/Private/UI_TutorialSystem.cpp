// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleTutorial/Public/UI_TutorialSystem.h"
#include "MediaAssets/Public/MediaPlayer.h"
#include "Tutorial/UI_TutorialSlot.h"
#include "components/Image.h"
#include "Components/CheckBox.h"
#include "components/Slider.h"
#include "components/TextBlock.h"
#include "Components/Button.h"

void UUI_TutorialSystem::NativeConstruct()
{
	Super::NativeConstruct();
	InitMedia(1);

	MediaPlayer->OnEndReached.AddDynamic(this, &UUI_TutorialSystem::FinishPlayMovie);


	ReplayButton->OnClicked.AddDynamic(this, &UUI_TutorialSystem::Replay);
	CloseButton->OnClicked.AddDynamic(this, &UUI_TutorialSystem::Close);
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

void UUI_TutorialSystem::InitMedia(bool IsPlayMovie)
{
	if (UUI_TutorialSlot* TutorialSlot = CreateWidget<UUI_TutorialSlot>(this, TutorialSlotClass, FName(TEXT("TutorialSlot"))))
	{
		if (MediaPlayer)
		{
			MediaPlayer->OpenSource(TutorialSlot->MediaSource);
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

void UUI_TutorialSystem::Close()
{
	if (MediaPlayer->IsPlaying())
	{
		MediaPlayer->Pause();
		PauseImage->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		SuspendButton->SetCheckedState(ECheckBoxState::Unchecked);

	}
	MediaPlayer->Close();
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
