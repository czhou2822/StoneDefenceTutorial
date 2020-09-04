// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/GameCore/TowerDefencePlayerController.h"
#include "Global/UI_Data.h"
#include "Engine/World.h"
#include "Core/GameCore/TowerDefenceGameCamera.h"
#include "StoneDefence/StoneDefenceGameMode.h"
#include "Character/Core/RuleOfTheCharacter.h"
#include "StoneDefence/Public/Core/GameCore/TowerDefenceGameState.h"
#include "StoneDefence/StoneDefenceUtils.h"
#include "StoneDefence/Public/UI/GameUI/Core/RuleofTheHUD.h"


ATowerDefencePlayerController::ATowerDefencePlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
}

void ATowerDefencePlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	float ScreenMoveSpeed = 20.f;
	ScreenMoveUnits.ListenScreenMove(this, ScreenMoveSpeed);

	if (TowerDoll)
	{
		if (MouseTraceHit.Location != FVector::ZeroVector)
		{
			MouseTraceHit = FHitResult();
		}

		FHitResult TraceOutHit;
		GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel4, true, TraceOutHit);
		TowerDoll->SetActorLocation(TraceOutHit.Location);
	}
	else
	{
		GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel5, true, MouseTraceHit);
	}

}

void ATowerDefencePlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetInputModeGameAndUI();
}

void ATowerDefencePlayerController::SetInputModeGameAndUI()
{
	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	InputMode.SetHideCursorDuringCapture(false);

	SetInputMode(InputMode);
}

ATowerDefenceGameState* ATowerDefencePlayerController::GetGameState()
{
	return GetWorld()->GetGameState<ATowerDefenceGameState>();
}

void ATowerDefencePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("MouseWheelUp", IE_Pressed, this, &ATowerDefencePlayerController::MouseWheelUp);
	InputComponent->BindAction("MouseWheelDown", IE_Pressed, this, &ATowerDefencePlayerController::MouseWheelDown);

	InputComponent->BindAction("MouseMiddleButton", IE_Pressed, this, &ATowerDefencePlayerController::MouseMiddleButtonPressed);
	InputComponent->BindAction("MouseMiddleButton", IE_Released, this, &ATowerDefencePlayerController::MouseMiddleButtonReleased);
}

static float WheelValue = 15.f;
void ATowerDefencePlayerController::MouseWheelUp()
{
	ATowerDefenceGameCamera* ZoomCamera = Cast<ATowerDefenceGameCamera>(GetPawn());
	if (ZoomCamera)
	{
		ZoomCamera->Zoom(true, WheelValue);
	}
}

void ATowerDefencePlayerController::MouseWheelDown()
{
	ATowerDefenceGameCamera* ZoomCamera = Cast<ATowerDefenceGameCamera>(GetPawn());
	if (ZoomCamera)
	{
		ZoomCamera->Zoom(false, WheelValue);
	}
}

void ATowerDefencePlayerController::MouseMiddleButtonPressed()
{
	EventMouseMiddlePressed.ExecuteIfBound();
}

void ATowerDefencePlayerController::MouseMiddleButtonReleased()
{
	EventMouseMiddleReleased.ExecuteIfBound();
}

const FHitResult& ATowerDefencePlayerController::GetHitResult()
{
	return MouseTraceHit;
}

AStoneDefenceGameMode* ATowerDefencePlayerController::GetGameMode()
{
	return GetWorld()->GetAuthGameMode<AStoneDefenceGameMode>();
}

void ATowerDefencePlayerController::RemoveSkillSlot_Server(const FGuid& CharacterID, const FGuid& SlotID)
{
	TArray<ARuleOfTheCharacter*> Characters;
	StoneDefenceUtils::Execution(GetWorld(), CharacterID, [&](ARuleOfTheCharacter* InCharacter)
	{
		InCharacter->RemoveSkillSlot_Client(SlotID);
	});

}

void ATowerDefencePlayerController::AddSkillSlot_Server(const FGuid& CharacterID, const FGuid& SlotID)
{
	StoneDefenceUtils::Execution(GetWorld(), CharacterID, [&](ARuleOfTheCharacter* InCharacter)
	{
		InCharacter->AddSkillSlot_Client(SlotID);
	});
}

//void ATowerDefencePlayerController::SpawnBullet_Server(const FGuid& CharacterID, const FGuid& SlotID)
//{
//	StoneDefenceUtils::Execution(GetWorld(), CharacterID, [&](ARuleOfTheCharacter* InCharacter)
//	{
//		InCharacter->AddSkillSlot_Client(SlotID);
//	});
//}


void ATowerDefencePlayerController::SpawnBullet_Client(const FGuid& CharacterID, const int32& SkillID)
{
	if (const FSkillData* InData = GetGameState()->GetSkillData(SkillID))
	{
		StoneDefenceUtils::Execution(GetWorld(), CharacterID, [&](ARuleOfTheCharacter* InCharacter)
		{
			InCharacter->UpdateSkill(SkillID);
		});
	}
}

AMonsters* ATowerDefencePlayerController::SpawnMonster(int32 CharacterID, int32 CharacterLevel, const FVector& Location, const FRotator& Rotator)
{
	if (GetGameMode())
	{
		return GetGameMode()->SpawnMonster(CharacterID, CharacterLevel, Location, Rotator);
	}
	return nullptr;
}

ATowers* ATowerDefencePlayerController::SpawnTower(int32 CharacterID, int32 CharacterLevel, const FVector& Location, const FRotator& Rotator)
{
	if (GetGameMode())
	{
		return GetGameMode()->SpawnTower(CharacterID, CharacterLevel, Location, Rotator);
	}

	return nullptr;

}


void ATowerDefencePlayerController::UpdateInventory_Client(const FGuid& InventorySlotGUID, bool bInCD)
{
	if (ARuleofTheHUD* NewHUD = GetHUD<ARuleofTheHUD>())
	{
		NewHUD->UpdateInventorySlot(InventorySlotGUID, bInCD);
	}
}