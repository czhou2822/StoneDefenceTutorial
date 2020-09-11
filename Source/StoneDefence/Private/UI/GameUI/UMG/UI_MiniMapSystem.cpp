// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/GameUI/UMG/UI_MiniMapSystem.h"
#include "StoneDefence/StoneDefenceUtils.h"
#include "Components/Image.h"
#include "Engine/SceneCapture2D.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/CanvasPanel.h"
#include "Components/SceneCaptureComponent2D.h"
#include "StoneDefence/Public/Core/GameCore/TowerDefenceGameCamera.h"
#include "Global/RuleOfTheGlobal.h"
#include "Global/Blueprint/GlobalConfiguration.h"


void UUI_MiniMapSystem::NativeConstruct()
{
	Super::NativeConstruct();

	if (ASceneCapture2D* SceneCapture2D = RenderingUtils::SpawnSceneCapture2D(GetWorld(), CaptureClass, MapSize, 0.3f))
	{
		//MiniMapImage->SetBrushFromTexture(SceneCapture2D->GetCaptureComponent2D()->TextureTarget);
		MiniMapImage->SetBrushFromMaterial(Cast<UMaterialInterface>(MiniMapMat.GetObject()));
	}

	if (MiniMapImage)
	{
		if (UCanvasPanelSlot* ImagePanelSlot = Cast<UCanvasPanelSlot>(MiniMapImage->Slot))
		{
			ImagePanelSlot->SetSize(FVector2D(GLOBAL_MANAGEMENT_MACRO()->GetGlobalConfiguration()->MaxMiniMapSize));
		}
	}



}

void UUI_MiniMapSystem::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	//const TMap<FGuid, FCharacterData>& CharacterData = GetGameState()->GetCharacterData();

	//if (UCanvasPanelSlot* ImagePanelSlot = Cast<UCanvasPanelSlot>(MiniMapImage->Slot))
	//{

	//	const float MaxMiniMapSize		= GLOBAL_MANAGEMENT_MACRO()->GetGlobalConfiguration()->MaxMiniMapSize;
	//	const float MaxTargetArmLength	= GLOBAL_MANAGEMENT_MACRO()->GetGlobalConfiguration()->MaxTargetArmLength;


	//	FVector2D LocalSize2D = MyGeometry.GetDrawSize();

	//	FVector2D ZoomSize;
	//	//µØÍ¼Ëõ·Å
	//	{
	//		float TargetArmLength = Cast<ATowerDefenceGameCamera>(GetWorld()->GetFirstPlayerController()->GetPawn())->GetTargetArmLength();

	//		ZoomSize = FVector2D((MaxMiniMapSize / MaxTargetArmLength) * TargetArmLength);

	//		ImagePanelSlot->SetSize(ZoomSize);
	//	}

	//	FVector2D MinImageMapOffset;
	//	{
	//		FVector Location = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	//		MinImageMapOffset.Y = -(ZoomSize.X - (ZoomSize.X / MapSize.BigMapRealSize.X) * Location.X);
	//		MinImageMapOffset.X = -(ZoomSize.Y / MapSize.BigMapRealSize.Y) * Location.Y;

	//		ImagePanelSlot->SetPosition(MinImageMapOffset);
	//	}

	//	for (auto& Tmp : CharacterData)
	//	{
	//		if (Tmp.Value.Health > 0.f)
	//		{
	//			if (!IsExistence(Tmp.Key))
	//			{
	//				if (UImage* Point = NewObject<UImage>(GetWorld(), UImage::StaticClass()))
	//				{
	//					if (UCanvasPanelSlot* PanelSlot = MiniMap->AddChildToCanvas(Point))
	//					{
	//						PanelSlot->SetZOrder(1.0f);
	//						PanelSlot->SetAnchors(0.5f);

	//						Point->SetBrushFromTexture(Tmp.Value.Icon.LoadSynchronous());
	//						PanelSlot->SetSize(FVector2D(32.f));
	//						PanelSlot->SetAlignment(FVector2D(0.5f));
	//						CharacterIcons.Add(Tmp.Key, PanelSlot);
	//					}
	//				}
	//			}
	//			else
	//			{
	//				if (UCanvasPanelSlot* PanelSlot = CharacterIcons[Tmp.Key].Get())
	//				{

	//					FVector2D MinMapPos;
	//					MinMapPos.Y = ZoomSize.X - (ZoomSize.X / MapSize.BigMapRealSize.X) * Tmp.Value.Location.X + MinImageMapOffset.Y;
	//					MinMapPos.X = (ZoomSize.Y / MapSize.BigMapRealSize.Y) * Tmp.Value.Location.Y + MinImageMapOffset.X;

	//					ResetLocation(PanelSlot, MinMapPos, LocalSize2D);
	//				}
	//			}
	//		}
	//	}

	//	TArray<FGuid> RemoveGuid;
	//	for (auto& Tmp : CharacterIcons)
	//	{
	//		if (!CharacterData.Contains(Tmp.Key))
	//		{
	//			if (UCanvasPanelSlot* PanelSlot = CharacterIcons[Tmp.Key].Get())
	//			{
	//				MiniMap->RemoveChild(PanelSlot->Content);
	//				RemoveGuid.Add(Tmp.Key);
	//			}
	//		}
	//	}

	//	for (auto& Tmp : RemoveGuid)
	//	{
	//		CharacterIcons.Remove(Tmp);
	//	}
	//}



}

bool UUI_MiniMapSystem::IsExistence(const FGuid& ID)
{
	for (auto& Tmp : CharacterIcons)
	{
		if (Tmp.Key == ID)
		{
			return true;
		}
	}
	return false;
}

void UUI_MiniMapSystem::ResetLocation(UCanvasPanelSlot* PanelSlot, const FVector2D& MinMapPos, const FVector2D& LocalSize2D)
{
	FVector2D IconSize = PanelSlot->GetSize() / 2;

	auto IsRange = [&](const float& CompareValue, const float& Value)->bool
	{
		return Value > -CompareValue && Value < CompareValue;
	};

	FVector2D NewPos = MinMapPos;
	if (MinMapPos.X <= LocalSize2D.X &&
		MinMapPos.Y <= LocalSize2D.Y &&
		MinMapPos.X >= -LocalSize2D.X &&
		MinMapPos.Y >= -LocalSize2D.Y)
	{

	}
	else if (MinMapPos.Y <-LocalSize2D.Y && IsRange(LocalSize2D.X, MinMapPos.X)) // 上
	{
		NewPos = FVector2D(MinMapPos.X, -LocalSize2D.Y + IconSize.Y);
	}
	else if (MinMapPos.X < -LocalSize2D.X && IsRange(LocalSize2D.Y, MinMapPos.Y)) // 左
	{
		NewPos = FVector2D(MinMapPos.X + LocalSize2D.Y, IconSize.Y);
	}
	else if (MinMapPos.Y > -LocalSize2D.Y && IsRange(LocalSize2D.X, MinMapPos.X)) // 下
	{
		NewPos = FVector2D(MinMapPos.X, LocalSize2D.Y - IconSize.Y);
	}
	else if (MinMapPos.X > -LocalSize2D.X && IsRange(LocalSize2D.Y, MinMapPos.Y)) // 右
	{
		NewPos = FVector2D(MinMapPos.X - LocalSize2D.X, IconSize.Y);
	}

	else if (MinMapPos.X < -LocalSize2D.X && MinMapPos.Y < -LocalSize2D.Y) //左上
	{
		NewPos = -LocalSize2D + IconSize;
	}
	else if (MinMapPos.X < -LocalSize2D.X && MinMapPos.Y > LocalSize2D.Y) //左下
	{
		NewPos = FVector2D(-LocalSize2D.X + IconSize.X, LocalSize2D.Y - IconSize.Y);
	}
	else if (MinMapPos.X > -LocalSize2D.X && MinMapPos.Y > -LocalSize2D.Y) //右下
	{
		NewPos = LocalSize2D - IconSize;
	}
	else if (MinMapPos.X > LocalSize2D.X && MinMapPos.Y < -LocalSize2D.Y) //右上
	{
		NewPos = FVector2D(LocalSize2D.X - IconSize.X, -LocalSize2D.Y + IconSize.Y);
	}


	PanelSlot->SetPosition(NewPos);
}
