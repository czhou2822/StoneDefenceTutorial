// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameUI/UMG/Inventory/UI_Inventory.h"
#include "Core/GameCore/TowerDefenceGameState.h"
#include "core/GameCore/TowerDefencePlayerController.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "Components/StaticMeshComponent.h"
#include "engine/StaticMeshActor.h"
#include "UI/GameUI/UMG/Inventory/UI_InventorySlot.h"
#include "UI/Core/UI_Data.h"


void UUI_Inventory::NativeConstruct()
{
	Super::NativeConstruct();

	LayoutInventorySlot(3,7);

	GetPlayerController()->EventMouseMiddlePressed.BindUObject(this, &UUI_Inventory::SpawnTowerDollPressed);

	GetPlayerController()->EventMouseMiddleReleased.BindUObject(this, &UUI_Inventory::SpawnTowerDollReleased);


}

FBuildingTower& UUI_Inventory::GetBuildingTower()
{
	return GetGameState()->GetBuildingTower(TowerICOGUID);
}

void UUI_Inventory::LayoutInventorySlot(int32 ColumnNumber, int32 RowNumber)
{
	if (InventorySlotClass)
	{
		for (int32 MyRow = 0; MyRow < RowNumber; MyRow++)
		{
			for (int32 MyColumn = 0; MyColumn < ColumnNumber; MyColumn++)
			{
				UUI_InventorySlot* SlotWidget = CreateWidget<UUI_InventorySlot>(GetWorld(), InventorySlotClass);
				if (SlotWidget)
				{
					UUniformGridSlot* GridSlot = SlotArrayInventory->AddChildToUniformGrid(SlotWidget);
					if (GridSlot)
					{
						GridSlot->SetColumn(MyColumn);
						GridSlot->SetRow(MyRow);
						GridSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
						GridSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
					}

					InventorySlotArray.Add(SlotWidget);
				}
			}
		}

		const TArray<const FGuid*> ID = GetGameState()->GetBuildingTowersID();

		for (int32 i = 0; i < ColumnNumber * RowNumber; i++)
		{
			InventorySlotArray[i]->GUID = *ID[i];
		}

		TArray<const FCharacterData*> Data;
		if (GetGameState()->GetTowerDataFormTable(Data))
		{
			for (int32 i = 0; i < Data.Num(); i++)
			{
				InventorySlotArray[i]->GetBuildingTower().TowerID = Data[i]->ID;
				InventorySlotArray[i]->GetBuildingTower().NeedGold = Data[i]->Gold;
				InventorySlotArray[i]->GetBuildingTower().MaxConstructionTowersCD = Data[i]->ConstructionTime;
				InventorySlotArray[i]->GetBuildingTower().ICO = Data[i]->Icon.LoadSynchronous();

				InventorySlotArray[i]->UpdateUI();
			}
		}



	}
}

void UUI_Inventory::SpawnTowerDollPressed()
{
	if (GetBuildingTower().IsValid())
	{
		bLockGUID = true;
		if (GetBuildingTower().TowersConstructionNumber >= 1)
		{
			int32 TowerID = GetBuildingTower().TowerID;
			if (AStaticMeshActor* MeshActor = GetGameState()->SpawnTowersDoll(TowerID))
			{
				for (int32 i = 0; i < MeshActor->GetStaticMeshComponent()->GetNumMaterials(); i++)
				{
					MeshActor->GetStaticMeshComponent()->SetMaterial(i, DollMaterial);

				}
				TowerDoll = MeshActor;
			}
		}
	}
}

void UUI_Inventory::SpawnTowerDollReleased()
{
	if (GetBuildingTower().IsValid())
	{
		if (TowerDoll)
		{
			if (GetBuildingTower().TowersConstructionNumber >= 1)
			{
				if (AActor* CharacterActor = GetGameState()->SpawnTower(GetBuildingTower().TowerID, 1, TowerDoll->GetActorLocation(), TowerDoll->GetActorRotation()))
				{
					GetBuildingTower().TowersConstructionNumber--;
				}
			}
			TowerDoll->Destroy();
			TowerDoll = nullptr;
		}
	}

	bLockGUID = false;

	TowerICOGUID = FGuid();
}
