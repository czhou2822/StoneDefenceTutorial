// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/Core/DataCore.h"
#include "Data/SkillData.h"
#include "CharacterData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FCharacterData : public FDataCore
{
	GENERATED_BODY()

public:

	////////////////////////////////////////////////////////////////////////////////////////
	//blueprint instance
	UPROPERTY(EditDefaultsOnly, Category = "Table")
	TAssetSubclassOf<class ARuleOfTheCharacter> CharacterBlueprintKey;

	UPROPERTY(EditDefaultsOnly, Category = "Table")
	TAssetPtr<class UTexture2D> Icon;

	////////////////////////////////////////////////////////////////////////////


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Attribute")
	float Lv;

	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
	float MaxHealth;

	UPROPERTY()
	float Health;

	//basic attack
	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
	float PhysicalAttack;

	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
	float Armor;

	//exp
	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
	float MaxEmpircalValue;

	UPROPERTY()
	float EmpircalValue;

	//Cooldown
	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
	float CD;

	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
	float AttackSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
	float Gold;

	UPROPERTY(EditDefaultsOnly, Category = "Character Attribute")
	FText Introduction;

	//growth
	////////////////////////////////////////////////////////////////////////////
	UPROPERTY(EditDefaultsOnly, Category = "Character Profit")
	float AddGold;

	UPROPERTY(EditDefaultsOnly, Category = "Character Profit")
	float AddHealth;

	UPROPERTY(EditDefaultsOnly, Category = "Character Profit")
	float AddPhysicalAttack;

	UPROPERTY(EditDefaultsOnly, Category = "Character Profit")
	float AddArmor;

	UPROPERTY(EditDefaultsOnly, Category = "Character Profit")
	float AddEmpiricalValue;

	UPROPERTY(EditDefaultsOnly, Category = "Character Profit")
	float AddAttackSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Character Profit")
	float RestoreHealth;

	UPROPERTY()
	FVector Location;

	UPROPERTY()
	FRotator Rotation;

	UPROPERTY()
	TEnumAsByte<ETeam> Team;
	
	//tower skill 
	////////////////////////////////////////////////////////////////////////////////////////


	//skill
	////////////////////////////////////////////////////////////////////////////////////////


	UPROPERTY()
	TArray<FSkillData> CharacterSkill;

	UPROPERTY()
	TMap<FGuid,FSkillData> AdditionalSkillData;


public:
	FCharacterData();

	virtual void Init() override;

	float GetEPPercent() const;

	void UpdateHealth();

	bool UpdateEP(float InExp);

	void UpdateLevel();

	float GetMaxHealth() const;

	float GetAttack() const;

	float GetArmor() const;

	float GetCD() const;

	float GetAttackSpeed() const;

};
