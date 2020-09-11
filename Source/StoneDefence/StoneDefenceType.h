// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "StoneDefenceType.generated.h"

UENUM(BlueprintType)
enum class EMiniMapType : uint8
{
	REAL_MAP,     
	GRAPHICAL_MAP,   
};


UENUM(BlueprintType)
enum class ESubmissionSkillRequestType : uint8
{
	AUTO,     //����Ȩ������������
	MANUAL,   //����Ȩ�������ͻ���
};



UENUM(BlueprintType)
enum class ESkillType : uint8
{
	BURST,
	SECTION,
	ITERATION,

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
		,TargetType(ESkillTargetType::FRIENDLY_FORCE)
		,SkillEffectType(ESkillEffectType::ADD)
	{

	}
	UPROPERTY(EditDefaultsOnly, Category = "Type")
	ESkillType SkillType;

	UPROPERTY(EditDefaultsOnly, Category = "Type")
	ESkillTargetType TargetType;
	
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
	BULLET_DIRECTLINE,     //���ϰ�ֱ�߹���
	BULLET_LINE,           //�Ǹ������ͣ� ������ǹ�ӵ�
	BULLET_TRACKLINE,      //��������
	BULLET_TRACKLINE_SP,   //��������
	BULLET_RANGELINE,      //��Χ�˺��� ������
	BULLET_RANGE,          //��Χ�˺��� �����Ա�
	BULLET_CHAIN,          //�������ͣ�DOT
};


UENUM(BlueprintType)
enum class ECharacterType : uint8
{
	TOWER,
	MONSTER,
	
};

struct FMapSize
{
	FVector2D BigMapRealSize;
};