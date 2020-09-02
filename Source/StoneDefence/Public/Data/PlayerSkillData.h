#pragma once

#include "CoreMinimal.h"
#include "Data/Core/DataCore.h"
#include "Data/SkillData.h"
#include "PlayerSkillData.generated.h"


USTRUCT(BlueprintType)
struct FPlayerSkillData : public FSkillData
{
    GENERATED_BODY()

    FPlayerSkillData();

    virtual void Init();

    UPROPERTY(EditDefaultsOnly, Category = "Skill Profit")
    float SkillNumber;


};