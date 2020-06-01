// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_TutorialSystem.generated.h"

/**
 * 
 */

class UCheckBox;
class UButton;
class USlider;
class UImage;
class UTextBlock;
class UMediaPlayer;
class UUI_TutorialSlot;

UCLASS()
class SIMPLETUTORIAL_API UUI_TutorialSystem : public UUserWidget
{
	GENERATED_BODY()


	UPROPERTY(meta = (BindWidget))
	UCheckBox* MainBoard;

	UPROPERTY(meta = (BindWidget))
	UButton* ReplayButton;

	UPROPERTY(meta = (BindWidget))
	UCheckBox* SuspendButton;

	UPROPERTY(meta = (BindWidget))
	UButton* CloseButton;

	UPROPERTY(meta = (BindWidget))
	UButton* PauseButton;

	UPROPERTY(meta = (BindWidget))
	USlider* MovieProgress;

	UPROPERTY(meta = (BindWidget))
	UImage* PauseImage;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayTimeText;

public:

	UPROPERTY(EditAnywhere, Category = UI)
	UMediaPlayer* MediaPlayer;

	UPROPERTY(EditAnywhere, Category = UI)
	TSubclassOf<UUI_TutorialSlot> TutorialSlotClass;


private:

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION()
	void InitMedia(bool IsPlayMovie);

	UFUNCTION()
	void ActivationMovie();

	UFUNCTION()
	void ClickedCheckBox(bool ClickedWidget);

	UFUNCTION()
	void Replay();

	UFUNCTION()
	void Close();

	UFUNCTION()
	void Pause();

	UFUNCTION()
	void FinishPlayMovie();

	UFUNCTION()
	void MouseCaptureBegin();

	UFUNCTION()
	void MouseCaptureEnd();

};
