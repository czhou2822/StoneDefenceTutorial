// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_TutorialSlot.generated.h"


class UButton;

/**
 * 
 */
UCLASS()
class SIMPLETUTORIAL_API UUI_TutorialSlot : public UUserWidget
{
	GENERATED_BODY()


	UPROPERTY(meta = (BindWidget))
	UButton* PlayButton;

protected:
	virtual void NativeConstruct() override;

public:
	UUI_TutorialSlot(const FObjectInitializer& ObjectInitializer);


	UPROPERTY()
	int32 Index;

	bool IsIndexValid();

	UFUNCTION()
	void SlotPlay();

};
