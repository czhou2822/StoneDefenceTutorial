#pragma once

#include "CoreMinimal.h"
#include "Core/DataCore.h"
#include "Stonedefence/StoneDefenceType.h"
#include "SkillData.generated.h"

class ARuleOfTheBulletl;

USTRUCT(BlueprintType)
struct FSkillData : public FDataCore
{
	GENERATED_USTRUCT_BODY()

		typedef FDataCore Super;

	FSkillData();

	virtual void Init() override;

	UPROPERTY(EditDefaultsOnly, Category = "Skill Attribute")
	FSkillType SkillType;

	UPROPERTY(EditDefaultsOnly, Category = "Skill Attribute")
	TAssetPtr<class UTexture2D> Icon;

	UPROPERTY(EditDefaultsOnly, Category = "Skill Attribute")
	TSubclassOf<AActor> BulletClass;   //instance of this data

	UPROPERTY(EditDefaultsOnly, Category = "Skill Attribute")
	FText SkillIntroduce;

	UPROPERTY()
	ESubmissionSkillRequestType SubmissionSkillRequestType;

	UPROPERTY(EditDefaultsOnly, Category = "Skill Profit")
	float Gold;

	UPROPERTY(EditDefaultsOnly, Category = "Skill Profit")
	float Health;

	UPROPERTY(EditDefaultsOnly, Category = "Skill Profit")
	float PhysicalAttack;

	UPROPERTY(EditDefaultsOnly, Category = "Skill Profit")
	float Armor;

	UPROPERTY(EditDefaultsOnly, Category = "Skill Profit")
	float AttackSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Skill Profit")
	float WalkSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Skill Profit")
	float AttackRange;

	UPROPERTY(EditDefaultsOnly, Category = "Dynamic Skills")
	float MaxSkillDuration;

	UPROPERTY()
	float SkillDuration;

	//skill effective interval
	UPROPERTY()
	float SkillDurationTime;

	UPROPERTY(EditDefaultsOnly, Category = "Main Skill")
	float CD;

	UPROPERTY()
	float CDTime;

	UPROPERTY()
	bool bBecomeEffective;

	float GetDurationPercent() const;

	float GetCDPercent() const;

	void ResetDuration();

	void ResetCD();

	friend bool operator==(const FSkillData& X, const FSkillData& Y)
	{
		return X.ID == Y.ID;
	}
};
