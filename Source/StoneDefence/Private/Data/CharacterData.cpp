#include "Data/CharacterData.h"
#include "stonedefence/StoneDefenceMacro.h"

FCharacterData::FCharacterData()
	:Super()

{

}

void FCharacterData::Init()
{
	Super::Init();

	Name = NAME_None;
	ID = INDEX_NONE;
	Lv = 0; 
		MaxHealth = 100;
	Health = MaxHealth;
	PhysicalAttack = 10;
	Armor = 10;
	MaxEmpircalValue = 100;
	EmpircalValue = 0.f;
	CD = 2.f;
	AttackSpeed = 0.66;
	Gold = 80;

	AddGold = 30;
	AddHealth = 50.f;
	AddPhysicalAttack = 10.f;
	AddArmor = 8.f;
	AddEmpiricalValue = 100;
	AddAttackSpeed = 0.001f;
	RestoreHealth = 0.2f;
	WalkSpeed = 356.f;

	Location = FVector::ZeroVector;
	Rotation = FRotator::ZeroRotator;

	Team = ETeam::RED;

}

float FCharacterData::GetEPPercent() const
{
	if (MaxEmpircalValue!=0.f)
	{
		return EmpircalValue / MaxEmpircalValue;
	}
	return 0.0f;
}

void FCharacterData::UpdateHealth()
{
	Health = GetMaxHealth();
}

bool FCharacterData::UpdateEP(float InExp)
{
	EmpircalValue += InExp;
	if (EmpircalValue >= MaxEmpircalValue)  //LEVEL UP
	{
		EmpircalValue -= EmpircalValue;

		UpdateLevel();
	}
	return false;
}

void FCharacterData::UpdateLevel()
{
	float Coefficient = 0.1f;

	Lv ++;
	Gold += (Lv - 1) * AddGold * Coefficient;
	MaxHealth += (Lv - 1) * AddHealth * Coefficient;
	PhysicalAttack += (Lv - 1) * AddPhysicalAttack * Coefficient;
	AttackSpeed += (Lv - 1) * AttackSpeed * Coefficient;
	Armor += (Lv - 1) * Armor * Coefficient;
	MaxEmpircalValue += (Lv - 1) * MaxEmpircalValue * Coefficient;
	RestoreHealth += (RestoreHealth * Lv) / 100;


	//AddPassiveSkillHealth += ((Lv - 1) * AddPassiveSkillHealth) * (Coefficient - 0.09f);
	//AddPassiveSkillPhysicalAttack += (Lv - 1) * AddPassiveSkillPhysicalAttack * (Coefficient - 0.09f);
	//AddPassiveSkillAttackSpeed += ((Lv - 1) * AddPassiveSkillAttackSpeed) * (Coefficient - 0.09f);
	//AddPassiveSkillArmor += ((Lv - 1) * AddPassiveSkillArmor) * (Coefficient - 0.09f);


	Health = GetMaxHealth();
}

float FCharacterData::GetMaxHealth() const
{
	SKILL_TABLE_ACQUISITION(MaxHealth, Health);
}

float FCharacterData::GetAttack() const
{
	SKILL_TABLE_ACQUISITION(PhysicalAttack, PhysicalAttack);
}

float FCharacterData::GetArmor() const
{
	SKILL_TABLE_ACQUISITION(Armor, Armor);
}

float FCharacterData::GetCD() const
{
	SKILL_TABLE_ACQUISITION_CD(CD);
}

float FCharacterData::GetAttackSpeed() const
{
	SKILL_TABLE_ACQUISITION(AttackSpeed, AttackSpeed);

}

float FCharacterData::GetWalkSpeed() const
{
	SKILL_TABLE_ACQUISITION(AttackSpeed, AttackSpeed);
}



