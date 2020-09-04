#include "Data/SkillData.h"




FSkillData::FSkillData()
	:Super()
{

}





void FSkillData::Init()
{
	Super::Init();

	Gold = 0.f;
	Health = 0.f;
	PhysicalAttack = 0.f;
	Armor = 0.f;
	AttackRange = 0.f;
	MaxSkillDuration = 5.f;
	SkillDuration = 0.f;
	WalkSpeed = 0.f;
	CD = 60.f;
	SkillDurationTime = 0.f;
	bBecomeEffective = false;
	SubmissionSkillRequestType = ESubmissionSkillRequestType::AUTO;
}

float FSkillData::GetDurationPercent() const
{
	return 0.0f;
}

float FSkillData::GetCDPercent() const
{
	return CD == 0.f ? 0 : (CDTime / CD);
}

void FSkillData::ResetDuration()
{
	SkillDuration = MaxSkillDuration;
}

void FSkillData::ResetCD()
{
	CDTime = CD;
}


