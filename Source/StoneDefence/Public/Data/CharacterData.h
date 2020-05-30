// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Data/SkillData.h"
#include "CharacterData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FCharacterData : public FTableRowBase
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
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Attribute")
	FName Name;

	//which characyter is it
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Attribute")
	int32 ID;  

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Attribute")
	int32 Lv;

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
	float AddPEmpiricalValue;

	UPROPERTY(EditDefaultsOnly, Category = "Character Profit")
	float AddAttackSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Character Profit")
	float RestoreHealth;
	
	//tower skill
	////////////////////////////////////////////////////////////////////////////////////////
	UPROPERTY(EditDefaultsOnly, Category = "Skill")
	float AddPassiveSkillHealth;

	UPROPERTY(EditDefaultsOnly, Category = "Skill")
	float AddContinueHealth;

	UPROPERTY(EditDefaultsOnly, Category = "Skill")
	float AddPassiveSkillPhysicalAttack;

	UPROPERTY(EditDefaultsOnly, Category = "Skill")
	float AddPassiveSkillArmor;

	UPROPERTY(EditDefaultsOnly, Category = "Skill")
	float AddPassiveSkillAttackSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Skill")
	float ReducePassiveSkillCDTime;

	UPROPERTY(EditDefaultsOnly, Category = "Build")
	float ConstructionTime;

	//skill
	////////////////////////////////////////////////////////////////////////////////////////
	UPROPERTY(EditDefaultsOnly, Category = "Character Skill")
	TMap<int32, FSkillData> CharacterSkill;



public:
	FCharacterData();

	bool IsValid() const;

	void UpdateHealth();

};
