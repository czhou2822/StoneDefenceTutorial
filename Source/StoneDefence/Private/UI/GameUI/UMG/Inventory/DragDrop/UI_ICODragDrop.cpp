// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/GameUI/UMG/Inventory/DragDrop/UI_ICODragDrop.h"
#include "Components/Image.h"
#include "Engine/Texture2D.h"

void UUI_ICODragDrop::DrawICON(UTexture2D* InICON)
{
	ICON->SetBrushFromTexture(InICON);
}
