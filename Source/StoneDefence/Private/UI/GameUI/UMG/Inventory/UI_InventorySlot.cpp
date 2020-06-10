// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/GameUI/UMG/Inventory/UI_InventorySlot.h"
#include "UI/GameUI/UMG/Inventory/DragDrop/UI_ICODragDrop.h"
#include "UI/GameUI/UMG/Tip/UI_TowerTip.h"
#include "UI/Core/UI_Data.h"
#include "core/GameCore/TowerDefenceGameState.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "DragDrop/StoneDefenceDragDropOperation.h"


#if PLATFORM_WINDOWS
#pragma optimize("", off)
#endif

void UUI_InventorySlot::NativeConstruct()
{
	Super::NativeConstruct();
	TowerISButton->OnClicked.AddDynamic(this, &UUI_InventorySlot::OnClickedWidget);

	if (TowerCD)
	{
		CDMaterialDynamic = TowerCD->GetDynamicMaterial();
	}
}

void UUI_InventorySlot::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (GetBuildingTower().IsValid())
	{
		if (!GetBuildingTower().bLockCD)
		{
			if (!GetBuildingTower().bDragICO)
			{
				UpdateTowerCD(InDeltaTime);

			}
		}
	}

}

void UUI_InventorySlot::UpdateTowerCD(float InDeltaTime)
{
	if (GetBuildingTower().CurrentConstructionTowersCD > 0)
	{
		DrawTowersCD(GetBuildingTower().GetTowerConstructionTimePercentage());
		GetBuildingTower().CurrentConstructionTowersCD -= InDeltaTime;
		GetBuildingTower().bCallUpdateTowerInfo = true;
		UpdateTowerBuildingInfo();
	}
	else if (GetBuildingTower().bCallUpdateTowerInfo)
	{
		GetBuildingTower().bCallUpdateTowerInfo = false;

		GetBuildingTower().TowersPerpareBuildingNumber--;
		GetBuildingTower().TowersConstructionNumber++;

		DrawTowersCD(0.0f);

		if (GetBuildingTower().TowersPerpareBuildingNumber > 0)
		{
			GetBuildingTower().ResetCD();
		}
		UpdateTowerBuildingInfo();

	}

}

void UUI_InventorySlot::DrawTowersCD(float InTowerCD)
{
	if (CDMaterialDynamic)
	{
		if (InTowerCD > 0.0f && InTowerCD < 1.f)
		{
			CDMaterialDynamic->SetScalarParameterValue(TowerClearValueName, true);
			TowerCD->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		}
		else
		{
			CDMaterialDynamic->SetScalarParameterValue(TowerClearValueName, false);
			TowerCD->SetVisibility(ESlateVisibility::Hidden);
		}
		CDMaterialDynamic->SetScalarParameterValue(TowerMatCDName, InTowerCD);
	}
}



void UUI_InventorySlot::DisplayNumber(UTextBlock* TextNumberBlock, int32 TextNumber)
{
	if (TextNumber < 1 || !GetBuildingTower().IsValid())
	{
		TextNumberBlock->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		TextNumberBlock->SetText(FText::FromString(FString::Printf(TEXT("%02d"), TextNumber)));
		TextNumberBlock->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
}

void UUI_InventorySlot::UpdateTowerBuildingInfo()
{
	DisplayNumber(TowerCDValue, GetBuildingTower().CurrentConstructionTowersCD);
	DisplayNumber(TowerCDNumber, GetBuildingTower().TowersConstructionNumber);
	DisplayNumber(TowersPBNumber, GetBuildingTower().TowersPerpareBuildingNumber);
}

FReply UUI_InventorySlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.GetEffectingButton() == EKeys::RightMouseButton || InMouseEvent.IsTouchEvent())
	{
		FReply Reply = FReply::Handled();
		TSharedPtr<SWidget> SlateWidgetDrag = GetCachedWidget();

		if (SlateWidgetDrag.IsValid())
		{
			Reply.DetectDrag(SlateWidgetDrag.ToSharedRef(), EKeys::RightMouseButton);
			return Reply;
		}
	}

	return FReply::Handled();
}

void UUI_InventorySlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	if (GetBuildingTower().IsValid() && ICODragDropClass)
	{
		if (UUI_ICODragDrop* ICODragDrop = CreateWidget<UUI_ICODragDrop>(GetWorld(), ICODragDropClass))
		{
			if (UStoneDefenceDragDropOperation* StoneDefenceDragDropOperation = NewObject<UStoneDefenceDragDropOperation>(GetTransientPackage(), UStoneDefenceDragDropOperation::StaticClass()))
			{
				StoneDefenceDragDropOperation->SetFlags(RF_StrongRefOnFrame);
				ICODragDrop->DrawICON(GetBuildingTower().ICO);
				StoneDefenceDragDropOperation->DefaultDragVisual = ICODragDrop;
				StoneDefenceDragDropOperation->Payload = this;
				OutOperation = StoneDefenceDragDropOperation;

				GetBuildingTower().bDragICO = true;

				ClearSlot();
			}
		}

	}

	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
}

bool UUI_InventorySlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	
	bool bDrop = false;

	if(UStoneDefenceDragDropOperation* StoneDefenceDragDropOperation = Cast<UStoneDefenceDragDropOperation>(InOperation))
	{
		if (UUI_InventorySlot* MyInventorySlot = Cast<UUI_InventorySlot>(StoneDefenceDragDropOperation->Payload))
		{
			MyInventorySlot->GetBuildingTower().bDragICO = false;
			GetPlayerState()->RequestInventorySlotSwap(GUID, MyInventorySlot->GUID);

			UpdateUI();
			MyInventorySlot->UpdateUI();

			bDrop = true;
		}
	}

	return bDrop;
}

void UUI_InventorySlot::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (!bLockGUID)
	{
		TowerICOGUID = GUID;
	}
}

void UUI_InventorySlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	
}



void UUI_InventorySlot::OnClickedWidget()
{
	if (GetBuildingTower().IsValid() )
	{
		if (/*GetBuildingTower().NeedGold <= */ 1)
		{
			GetBuildingTower().TowersPerpareBuildingNumber++;
			if (GetBuildingTower().CurrentConstructionTowersCD <= 0)
			{
				GetBuildingTower().ResetCD();
			}
		}
	}
}

UWidget* UUI_InventorySlot::GetTowerTip()
{
	if (TowerTipClass)
	{
		if (UUI_TowerTip * TowerTip = CreateWidget<UUI_TowerTip>(GetWorld(), TowerTipClass))
		{
			const FCharacterData &TowerDataInfo = GetGameState()->GetCharacterDataByID(GetBuildingTower().TowerID);
			if (TowerDataInfo.IsValid())
			{
				TowerTip->InitTip(TowerDataInfo);



				return TowerTip;
			}


		}
	}
	return nullptr;
}

void UUI_InventorySlot::UpdateUI()
{
	if (GetBuildingTower().ICO)
	{
		TowerIcon->SetBrushFromSoftTexture(GetBuildingTower().ICO);
		TowerIcon->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
	else
	{
		TowerIcon->SetVisibility(ESlateVisibility::Hidden);
	}

	if (GetBuildingTower().CurrentConstructionTowersCD > 0)
	{
		TowerCD->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}

	if (GetBuildingTower().TowersConstructionNumber > 0)
	{
		TowerCDNumber->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}

	if (GetBuildingTower().TowersPerpareBuildingNumber > 0)
	{
		TowersPBNumber->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
}

FBuildingTower& UUI_InventorySlot::GetBuildingTower()
{
	return GetPlayerState()->GetBuildingTower(GUID);
}

void UUI_InventorySlot::ClearSlot()
{
	TowerIcon->SetVisibility(ESlateVisibility::Hidden);
	TowerCD->SetVisibility(ESlateVisibility::Hidden);
	TowersPBNumber->SetVisibility(ESlateVisibility::Hidden);
	TowerCDValue->SetVisibility(ESlateVisibility::Hidden);
	TowerCDNumber->SetVisibility(ESlateVisibility::Hidden);
}



#if PLATFORM_WINDOWS
#pragma optimize("", on)
#endif