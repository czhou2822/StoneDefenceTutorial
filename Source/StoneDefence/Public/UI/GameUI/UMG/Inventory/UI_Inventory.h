// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/GameUI/UMG/Core/UI_Slot.h"
#include "UI_Inventory.generated.h"


class UUniformGridPanel;
class UUI_InventorySlot;

/**
 * 
 */
UCLASS()
class STONEDEFENCE_API UUI_Inventory : public UUI_Slot
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	UUniformGridPanel* SlotArrayInventory;

	UPROPERTY(EditDefaultsOnly, Category = UI)
	TSubclassOf<UUI_InventorySlot> InventorySlotClass;

	UPROPERTY(EditDefaultsOnly, Category = UI)
	UMaterialInterface* DollMaterial;

private:
	TArray<UUI_InventorySlot*> InventorySlotArray;


protected:

	virtual void NativeConstruct();

	void LayoutInventorySlot(int32 ColumnNumber, int32 RowNumber);

	FBuildingTower& GetBuildingTower();

	void SpawnTowerDollPressed(); 

	void SpawnTowerDollReleased();
	 
public:
	void UpdateInventorySlot(const FGuid& InventorySlotGUID, bool bInCD);


	
};
