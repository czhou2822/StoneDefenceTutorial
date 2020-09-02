// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "StoneDefenceType.generated.h"


UENUM(BlueprintType)
enum class ESubmissionSkillRequestType : uint8
{
	AUTO,     //生成权力交给服务器
	MANUAL,   //生成权力交给客户部
};



UENUM(BlueprintType)
enum class ESkillType : uint8
{
	BURST,
	SECTION,
	ITERATION,

};

UENUM(BlueprintType)
enum class ESkillAttackType : uint8
{
	SINGLE,
	MULTIPLE,
};

UENUM(BlueprintType)
enum class ESkillTargetType : uint8
{
	FRIENDLY_FORCE,
	ENEMY,
};

UENUM(BlueprintType)
enum class ESkillEffectType : uint8
{
	ADD,
	SUBTRACT,
};

USTRUCT(BlueprintType)
struct FSkillType
{
	GENERATED_USTRUCT_BODY()
	FSkillType()
		:SkillType(ESkillType::SECTION)
		,SkillTargetType(ESkillTargetType::FRIENDLY_FORCE)
		,SkillAttackType(ESkillAttackType::MULTIPLE)
		,SkillEffectType(ESkillEffectType::ADD)
	{

	}
	UPROPERTY(EditDefaultsOnly, Category = "Type")
	ESkillType SkillType;

	UPROPERTY(EditDefaultsOnly, Category = "Type")
	ESkillTargetType SkillTargetType;

	UPROPERTY(EditDefaultsOnly, Category = "Type")
	ESkillAttackType SkillAttackType;
	
	UPROPERTY(EditDefaultsOnly, Category = "Type")
	ESkillEffectType SkillEffectType;

};



UENUM(BlueprintType)
enum ETeam
{
	RED,
	BLUE,
	MAX,
};


UENUM(BlueprintType)
namespace EGameCharacterType
{
	enum Type
	{
		MINI,
		BOSS,
		MAX,
	};
}

UENUM(BlueprintType)
enum class EBulletType : uint8
{
	BULLET_NONE,           //place holder
	BULLET_DIRECTLINE,     //无障碍直线攻击
	BULLET_LINE,           //非跟踪类型， 类似手枪子弹
	BULLET_TRACKLINE,      //跟踪类型
	BULLET_TRACKLINE_SP,   //跟踪类型
	BULLET_RANGELINE,      //范围伤害， 丢手雷
	BULLET_RANGE,          //范围伤害， 类似自爆
	BULLET_CHAIN,          //链条类型，DOT
};


UENUM(BlueprintType)
enum class ECharacterType : uint8
{
	TOWER,
	MONSTER,
	
};

