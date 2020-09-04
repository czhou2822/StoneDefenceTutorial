// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameUI/UMG/Core/UI_Slot.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UUI_Slot::NativeConstruct()
{
	Super::NativeConstruct();

	ClickButton->OnClicked.AddDynamic(this, &UUI_Slot::OnClickedWidget);

	CDMaterialDynamic = SlotCD->GetDynamicMaterial();
}

void UUI_Slot::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UUI_Slot::ClearSlot()
{
	SlotIcon->SetVisibility(ESlateVisibility::Hidden);
	SlotCD->SetVisibility(ESlateVisibility::Hidden);
	SlotCDValue->SetVisibility(ESlateVisibility::Hidden);
	SlotNumber->SetVisibility(ESlateVisibility::Hidden);
}

void UUI_Slot::UpdateSloInfo(int32 ConstructionNumber, float InSlotCD)
{
	DisplayNumber(SlotCDValue, InSlotCD);
	DisplayNumber(SlotNumber, ConstructionNumber);
}

void UUI_Slot::UpdateSlotUI(UTexture2D* ICO, int32 ConstructionNumber)
{
	if (ICO)
	{
		SlotIcon->SetBrushFromTexture(ICO);
		SlotIcon->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
	else
	{
		SlotIcon->SetVisibility(ESlateVisibility::Hidden);
	}

	if (ConstructionNumber > 0)
	{
		SlotNumber->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
}

void UUI_Slot::DrawSlotCD(float InSlotCD)
{
	if (CDMaterialDynamic)
	{
		if (InSlotCD > 0.0f && InSlotCD < 1.0f)
		{
			CDMaterialDynamic->SetScalarParameterValue(SlotClearValueName, true);
			SlotCD->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		}
		else
		{
			CDMaterialDynamic->SetScalarParameterValue(SlotClearValueName, false);
			SlotCD->SetVisibility(ESlateVisibility::Hidden);
		}

		CDMaterialDynamic->SetScalarParameterValue(SlotMatCDName, InSlotCD);
	}
}

void UUI_Slot::DisplayNumber(UTextBlock* TextNumberBlock, float TextNumber)
{
	if (TextNumber <= 0.f)
	{
		TextNumberBlock->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		if (TextNumber > 0.f && TextNumber <= 1.0f)
		{
			TextNumberBlock->SetText(FText::FromString(FString::Printf(TEXT("%.1f"), TextNumber)));
		}
		else
		{
			TextNumberBlock->SetText(FText::FromString(FString::Printf(TEXT("%02d"), (int32)TextNumber)));
		}

		TextNumberBlock->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
}

void UUI_Slot::DisplayNumber(UTextBlock* TextNumberBlock, int32 TextNumber)
{
	if (TextNumber < 1)
	{
		TextNumberBlock->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		TextNumberBlock->SetText(FText::FromString(FString::Printf(TEXT("%02d"), TextNumber)));

		TextNumberBlock->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
}
