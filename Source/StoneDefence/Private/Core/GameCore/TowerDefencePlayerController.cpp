// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/GameCore/TowerDefencePlayerController.h"
#include "UI/Core/UI_Data.h"
#include "Engine/World.h"
#include "Core/GameCore/TowerDefenceGameCamera.h"
#include "StoneDefence/StoneDefenceGameMode.h"



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
