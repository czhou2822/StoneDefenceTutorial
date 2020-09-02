#pragma once


#include "Data\PlayerSkillData.h"


FPlayerSkillData::FPlayerSkillData()
	:FSkillData()
{

}

void FPlayerSkillData::Init()
{
	FSkillData::Init();
	SkillNumber = 0;
}
