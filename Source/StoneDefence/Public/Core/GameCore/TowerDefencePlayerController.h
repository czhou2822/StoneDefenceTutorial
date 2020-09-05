// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Tool/ScreenMove.h"
#include "TowerDefencePlayerController.generated.h"

/**
 * 
 */

DECLARE_DELEGATE_OneParam(FAddSkillDelegate, FGuid);
DECLARE_DELEGATE_TwoParams(FSpawnBulletDelegate, FGuid, UClass*);



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
	
	FAddSkillDelegate AddSkillDelegate;

	FSpawnBulletDelegate SpawnBulletDelegate;
public:

	ATowerDefencePlayerController();

	virtual void Tick(float DeltaSeconds) override;

	virtual void BeginPlay() override;

	void SetInputModeGameAndUI();

	class ATowerDefenceGameState* GetGameState();

	virtual void SetupInputComponent() override;

	void MouseWheelUp();

	void MouseWheelDown();

	void MouseMiddleButtonPressed();

	void MouseMiddleButtonReleased();

	void UpdateGlobalVar();

	const FHitResult& GetHitResult();

	class AStoneDefenceGameMode* GetGameMode();

	UFUNCTION(/*Server*/)
	void RemoveSkillSlot_Server(const FGuid& CharacterID, const FGuid& SlotID);

	UFUNCTION(/*Server*/)
	void AddSkillSlot_Server(const FGuid& CharacterID, const FGuid& SlotID);

	//UFUNCTION(/*Client*/)
	//void SpawnBullet_Server(const FGuid &CharacterID, const FGuid& SlotID);

	UFUNCTION(/*Client*/)
	void SpawnBullet_Client(const FGuid& CharacterID, const int32& SkillID);

	UFUNCTION(/*Client*/)
	void UpdateInventory_Client(const FGuid& InventorySlotGUID, bool bInCD);

	UFUNCTION(/*Client*/)
	void SpawnPlayerSkill_Client(const int32& PlayerSkillID);

	UFUNCTION(/*Client*/)
	void UpdatePlayerSkill_Client(const FGuid& PlayerSlotGUID, bool bInCD);

	UFUNCTION()
	class AMonsters* SpawnMonster(int32 CharacterID, int32 CharacterLevel, const FVector& Location, const FRotator& Rotator);

	UFUNCTION()
	class ATowers* SpawnTower(int32 CharacterID, int32 CharacterLevel, const FVector& Location, const FRotator& Rotator);
	
};
