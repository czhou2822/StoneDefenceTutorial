// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "StoneDefenceType.generated.h"


UENUM()
namespace EGameCharacterType
{
	enum Type
	{
		TOWER,
		MAIN_TOWER,
		MONSTER,
		BOSS_MONSTER,
		MAX
	};
}

UENUM()
enum class EBulletType : uint8
{
	BULLET_DIRECTLINE,     //无障碍直线攻击
	BULLET_LINE,           //非跟踪类型， 类似手枪子弹
	BULLET_TRACKLINE,      //跟踪类型
	BULLET_TRACKLINE_SP,   //跟踪类型
	BULLET_RANGELINE,      //范围伤害， 丢手雷
	BULLET_RANGE,          //范围伤害， 类似自爆
	BULLET_CHAIN,          //链条类型，DOT
};


UENUM()
enum class ECharacterType : uint8
{
	TOWER,
	MONSTER,
	
};