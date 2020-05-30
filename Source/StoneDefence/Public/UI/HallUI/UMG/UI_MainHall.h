// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Core/UI_RuleOfTheWidget.h"
#include "UI_MainHall.generated.h"

/**
 * 
 */
UCLASS()
class STONEDEFENCE_API UUI_MainHall : public UUI_RuleOfTheWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	class UBorder* MainBoard;

	UPROPERTY(meta = (BindWidget))
	class USizeBox* BoxList;

	UPROPERTY(meta = (BindWidget))
	class UUI_HallMenuSystem* HallMenuSystem;

	UPROPERTY(EditDefaultsOnly, Category = UI)
	TSubclassOf<class UUI_ArchivesSystem> ArchivesSystemClass;

	UPROPERTY(EditDefaultsOnly, Category = UI)
	TSubclassOf<class UUI_GameSettingsSystem> GameSettingsClass;

	UPROPERTY(EditDefaultsOnly, Category = UI)
	TSubclassOf<class UUI_TutorialSystem> TutorialSystemClass;


public:
	virtual void NativeConstruct();

	UFUNCTION()
		void GameStart();

	UFUNCTION()
		void SecretTerritory();

	UFUNCTION()
		void History();

	UFUNCTION()
		void GameSettings();

	UFUNCTION()
		void TutorialWebsite();

	UFUNCTION()
		void Browser();

	UFUNCTION()
		void SpecialContent();

	UFUNCTION()
		void QuitGame();




};
