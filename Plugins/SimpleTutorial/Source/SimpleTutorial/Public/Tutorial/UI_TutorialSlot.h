// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI_TutorialSlot.generated.h"

class UMediaSource;

/**
 * 
 */
UCLASS()
class SIMPLETUTORIAL_API UUI_TutorialSlot : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	UMediaSource* MediaSource;
};
