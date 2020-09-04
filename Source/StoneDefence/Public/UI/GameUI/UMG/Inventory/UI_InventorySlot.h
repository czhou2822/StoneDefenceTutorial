// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/GameUI/UMG/Core/UI_Slot.h"
#include "Data/Save/GameSaveData.h"
#include "UI_InventorySlot.generated.h"

/**
 * 
 */
UCLASS()
class STONEDEFENCE_API UUI_InventorySlot : public UUI_Slot
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	class UImage* TowerIcon;

	UPROPERTY(meta = (BindWidget))
	class UImage* TowerCD;

	//Tower prepare building number
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TowersPBNumber;

	//Tower completion of construction number
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TowerCDNumber;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TowerCDValue;

	//tower inventory slot button
	UPROPERTY(meta = (BindWidget))
	class UButton* TowerISButton;

	UPROPERTY(EditdefaultsOnly, Category = UI)
	FName TowerMatCDName;

	UPROPERTY(EditdefaultsOnly, Category = UI)
	FName TowerClearValueName;

	UPROPERTY(EditdefaultsOnly, Category = UI)
	TSubclassOf<class UUI_ICODragDrop> ICODragDropClass;

	UPROPERTY(EditdefaultsOnly, Category = UI)
	TSubclassOf<class UUI_TowerTip> TowerTipClass;

	//UPROPERTY(EditdefaultsOnly, Category = UI)
	//TSubclassOf<class UStoneDefenceDragDropOperation> IcoDragDrop;

	//UPROPERTY()
	//class UMaterialInstanceDynamic* CDMaterialDynamic;

private:
	void UpdateTowerCD(float InDeltaTime);

	void DrawTowersCD(float TowerCD);

	void DisplayNumber(UTextBlock* TextNumberBlock, int32 TextNumber);

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

	void OnClickedWidget();


	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Tip)
	UWidget* GetTowerTip();


	void UpdateUI();

	FBuildingTower& GetBuildingTower();

	void ClearSlot();
	
};
