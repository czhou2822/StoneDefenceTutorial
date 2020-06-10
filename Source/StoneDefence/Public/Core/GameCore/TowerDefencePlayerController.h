// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Tool/ScreenMove.h"
#include "TowerDefencePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class STONEDEFENCE_API ATowerDefencePlayerController : public APlayerController
{
	GENERATED_BODY()



protected:

	FScreenMoveUnits ScreenMoveUnits;

	FHitResult MouseTraceHit;

public:
	FSimpleDelegate EventMouseMiddlePressed;

	FSimpleDelegate EventMouseMiddleReleased;


public:

	ATowerDefencePlayerController();

	virtual void Tick(float DeltaSeconds) override;

	virtual void BeginPlay() override;

	void SetInputModeGameAndUI();

	virtual void SetupInputComponent() override;

	void MouseWheelUp();

	void MouseWheelDown();

	void MouseMiddleButtonPressed();

	void MouseMiddleButtonReleased();

	const FHitResult& GetHitResult();

	class AStoneDefenceGameMode* GetGameMode();

	UFUNCTION()
	class AMonsters* SpawnMonster(int32 CharacterID, int32 CharacterLevel, const FVector& Location, const FRotator& Rotator);

	UFUNCTION()
	class ATowers* SpawnTower(int32 CharacterID, int32 CharacterLevel, const FVector& Location, const FRotator& Rotator);
	
};
