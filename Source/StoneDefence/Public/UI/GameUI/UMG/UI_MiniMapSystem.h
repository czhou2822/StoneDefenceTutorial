// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/GameUI/UMG/Drop/UI_NativeOnDrop.h"
#include "StoneDefence/StoneDefenceType.h"
#include "UI/Core/UI_RuleOfTheWidget.h"
#include "UI_MiniMapSystem.generated.h"


class UCanvasPanel;
class ASceneCapture2D;
class UImage;
class UMaterialInterface;
class UCanvasPanelSlot;
/**
 * 
 */
UCLASS()
class STONEDEFENCE_API UUI_MiniMapSystem : public UUI_NativeOnDrop
{
	GENERATED_BODY()

	
	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* MiniMap;


	UPROPERTY(meta = (BindWidget))
	UImage* MiniMapImage;

	UPROPERTY(EditDefaultsOnly, Category = UI)
	TSubclassOf<ASceneCapture2D> CaptureClass;

	UPROPERTY(EditDefaultsOnly, Category = UI)
	TScriptInterface<UMaterialInterface> MiniMapMat;

public:

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	bool IsExistence(const FGuid& ID);

	void ResetLocation(UCanvasPanelSlot* PanelSlot, const FVector2D& MinMapPos, const FVector2D& LocalSize2D);
protected:
	TMap<FGuid, TWeakObjectPtr<UCanvasPanelSlot>> CharacterIcons;

	FMapSize MapSize;

	
};
