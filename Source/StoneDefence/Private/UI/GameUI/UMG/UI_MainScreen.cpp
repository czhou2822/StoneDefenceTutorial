// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/GameUI/UMG/UI_MainScreen.h"
#include "character/Core/RuleOfTheCharacter.h"
#include "UI/GameUI/UMG/Inventory/DragDrop/UI_ICODragDrop.h"
#include "UI/GameUI/UMG/Inventory/UI_InventorySlot.h"
#include "UI/GameUI/UMG/Tip/UI_TowerTip.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"
#include "UI/Core/UI_Data.h"
#include "Components/Image.h"
#include "UI/GameUI/UMG/UI_RucksackSystem.h"


void UUI_MainScreen::NativeConstruct()
{
	Super::NativeConstruct();
}

void UUI_MainScreen::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	//show character tool tip
	if (ARuleOfTheCharacter *InCharacter = Cast<ARuleOfTheCharacter>(GetPlayerController()->GetHitResult().GetActor()))
	{
		const FCharacterData &CharacterData = GetGameState()->GetCharacterData(InCharacter->GUID);
		if (CharacterData.IsValid())
		{
			CharacterTip->InitTip(CharacterData);
			CharacterTip->SetVisibility(ESlateVisibility::HitTestInvisible);

			if (UCanvasPanelSlot* NewPanelSlot = Cast<UCanvasPanelSlot>(CharacterTip->Slot))
			{
				FVector2D ScreenLocation = FVector2D::ZeroVector;
				UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(GetPlayerController(), GetPlayerController()->GetHitResult().Location, ScreenLocation);
				NewPanelSlot->SetPosition(ScreenLocation);
			}
			else
			{
				CharacterTip->SetVisibility(ESlateVisibility::Hidden);
			}

		}
		else
		{
			CharacterTip->SetVisibility(ESlateVisibility::Hidden);
		}

	}
	else
	{
		CharacterTip->SetVisibility(ESlateVisibility::Hidden);
	}

	//show concentrated info
	if (ClickedTargetMonster && ClickedTargetMonster->IsActive())
	{
		if (UCanvasPanelSlot* NewPanelSlot = Cast<UCanvasPanelSlot>(FireConcentrationPoint->Slot))
		{
			FVector2D ScreenLocation = FVector2D::ZeroVector;
			UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(GetPlayerController(), ClickedTargetMonster->GetActorLocation(), ScreenLocation);
			NewPanelSlot->SetPosition(ScreenLocation);
			FireConcentrationPoint->SetVisibility(ESlateVisibility::HitTestInvisible);
		}
	}
	else
	{
		ClickedTargetMonster = nullptr;
		FireConcentrationPoint->SetVisibility(ESlateVisibility::Hidden);
	}

}

void UUI_MainScreen::UpdateInventorySlot(const FGuid& InventorySlotGUID, bool bInCD)
{
	if (RucksackSystem)
	{
		RucksackSystem->UpdateInventorySlot(InventorySlotGUID, bInCD);
	}
}
