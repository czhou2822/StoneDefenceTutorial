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
	AddEmpiricalValue(20),
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

bool FCharacterData::UpdateLevel(float InExp)
{
	EmpircalValue += InExp;
	if (EmpircalValue >= MaxEmpircalValue)  //LEVEL UP
	{
		EmpircalValue -= EmpircalValue;
		

		float Coefficient = 0.1f;

		Lv += 1;
		MaxHealth += (Lv - 1) * AddHealth * Coefficient;
		PhysicalAttack += (Lv - 1) * AddPhysicalAttack * Coefficient;
		AttackSpeed += (Lv - 1) * AttackSpeed * Coefficient;
		Armor += (Lv - 1) * Armor * Coefficient;
		MaxEmpircalValue += (Lv - 1) * MaxEmpircalValue * Coefficient;
		RestoreHealth += (RestoreHealth * Lv) / 100;


		AddPassiveSkillHealth += ((Lv - 1) * AddPassiveSkillHealth)* (Coefficient - 0.09f);
		AddPassiveSkillPhysicalAttack += (Lv - 1) * AddPassiveSkillPhysicalAttack * (Coefficient - 0.09f);
		AddPassiveSkillAttackSpeed += ((Lv - 1) * AddPassiveSkillAttackSpeed) * (Coefficient - 0.09f);
		AddPassiveSkillArmor += ((Lv - 1) * AddPassiveSkillArmor) * (Coefficient - 0.09f);


		Health = MaxHealth;
		return true;
	}
	return false;
}


