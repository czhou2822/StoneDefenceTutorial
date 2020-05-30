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
	BULLET_DIRECTLINE,     //���ϰ�ֱ�߹���
	BULLET_LINE,           //�Ǹ������ͣ� ������ǹ�ӵ�
	BULLET_TRACKLINE,      //��������
	BULLET_TRACKLINE_SP,   //��������
	BULLET_RANGELINE,      //��Χ�˺��� ������
	BULLET_RANGE,          //��Χ�˺��� �����Ա�
	BULLET_CHAIN,          //�������ͣ�DOT
};


UENUM()
enum class ECharacterType : uint8
{
	TOWER,
	MONSTER,
	
};