// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Core/UI_RuleOfTheWidget.h"
#include "UI_ICODragDrop.generated.h"

class UImage;
class UTexture2D;
/**
 * 
 */
UCLASS()
class STONEDEFENCE_API UUI_ICODragDrop : public UUI_RuleOfTheWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	class UImage* ICON;

public:
	void DrawICON(UTexture2D* InICON);
	
};
