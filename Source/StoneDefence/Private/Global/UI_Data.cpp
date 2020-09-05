#include "Global/UI_Data.h"
#include "Character/Core/RuleOfTheCharacter.h"


int32 PlayerSkillNumber = 0;

FGuid TowerICOGUID;
AActor* TowerDoll = nullptr;
bool bLockGUID = false;

ARuleOfTheCharacter* ClickedTargetTower = nullptr;
ARuleOfTheCharacter* ClickedTargetMonster = nullptr;