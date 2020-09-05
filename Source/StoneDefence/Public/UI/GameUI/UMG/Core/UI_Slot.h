// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Core/UI_RuleOfTheWidget.h"
#include "UI_Slot.generated.h"

class UImage;
class UTextBlock;
class UButton;
/**
 * 
 */
UCLASS()
class STONEDEFENCE_API UUI_Slot : public UUI_RuleOfTheWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	UImage* SlotIcon;

	UPROPERTY(meta = (BindWidget))
	UImage* SlotCD;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SlotNumber;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SlotCDValue;

	UPROPERTY(meta = (BindWidget))
	UButton* ClickButton;

	UPROPERTY(EditDefaultsOnly, Category = UI)
	FName SlotMatCDName;

	UPROPERTY(EditDefaultsOnly, Category = UI)
	FName SlotClearValueName;

	UPROPERTY()
	class UMaterialInstanceDynamic* CDMaterialDynamic;

public:
	virtual void NativeConstruct() override;
	//Tick
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual void ClearSlot();

	UFUNCTION(BlueprintCallable)
	virtual void OnClickedWidget() {}

public:
	void UpdateSlotInfo(int32 ConstructionNumber, float InSlotCD);

	void UpdateSlotUI(UTexture2D* ICO, int32 ConstructionNumber);

	void DrawSlotCD(float InSlotCD);

protected:
	void DisplayNumber(UTextBlock* TextNumberBlock, float TextNumber);

	void DisplayNumber(UTextBlock* TextNumberBlock, int32 TextNumber);
};