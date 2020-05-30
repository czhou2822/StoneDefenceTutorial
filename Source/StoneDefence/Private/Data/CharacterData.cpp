#include "Data/CharacterData.h"

FCharacterData::FCharacterData()
	:Name(NAME_None),
	ID(INDEX_NONE),
	Lv(1),
	MaxHealth(100),
	Health(MaxHealth),
	PhysicalAttack(10),
	Armor(10),
	MaxEmpircalValue(100),
	EmpircalValue(MaxEmpircalValue),
	CD(2.f),
	AttackSpeed(0.66),
	Gold(80),

	AddGold(30),
	AddHealth(0.f),
	AddPhysicalAttack(0.f),
	AddArmor(0.f),
	AddPEmpiricalValue(20),
	AddAttackSpeed(0.f),
	RestoreHealth(0.2f),

	AddPassiveSkillHealth(0.f),
	AddContinueHealth(0.f),
	AddPassiveSkillPhysicalAttack(0.f),
	AddPassiveSkillArmor(0),
	AddPassiveSkillAttackSpeed(0),
	ReducePassiveSkillCDTime(0.45f),
	ConstructionTime(5)

{

}

bool FCharacterData::IsValid() const
{
	return ID != INDEX_NONE;
}

void FCharacterData::UpdateHealth()
{
	Health = MaxHealth;
}


