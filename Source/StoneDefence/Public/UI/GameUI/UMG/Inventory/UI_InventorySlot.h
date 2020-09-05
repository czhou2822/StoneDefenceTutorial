// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/GameUI/UMG/Core/UI_Slot.h"
#include "Data/Save/GameSaveData.h"
#include "UI/Core/UI_RuleOfTheWidget.h"
#include "UI_InventorySlot.generated.h"

/**
 * 
 */
UCLASS()
class STONEDEFENCE_API UUI_InventorySlot : public UUI_Slot
{
	GENERATED_BODY()


	//Tower prepare building number
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TowersPBNumber;


	UPROPERTY(EditdefaultsOnly, Category = UI)
	TSubclassOf<class UUI_ICODragDrop> ICODragDropClass;

	UPROPERTY(EditdefaultsOnly, Category = UI)
	TSubclassOf<class UUI_TowerTip> TowerTipClass;




private:
	//void UpdateTowerCD(float InDeltaTime);

public:
	void UpdateTowerBuildingInfo();
	
protected:

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;



public:

	virtual void NativeConstruct();

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual void OnClickedWidget();


	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Tip)
	UWidget* GetTowerTip();


	void UpdateUI();

	FBuildingTower& GetBuildingTower();

	void ClearSlot();
	
};
