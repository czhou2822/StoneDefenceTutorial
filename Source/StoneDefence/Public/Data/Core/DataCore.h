#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "DataCore.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct FDataCore : public FTableRowBase
{
    GENERATED_BODY()

public:

    FDataCore();

    virtual void Init();

    virtual bool IsValid() const;

    UPROPERTY(EditDefaultsOnly, Category = "Attribute")
    FName Name;

    UPROPERTY(EditDefaultsOnly, Category = "Attribute")
    int32 ID;

    UPROPERTY(EditDefaultsOnly, Category = "Attribute")
    int32 GameGold;

    UPROPERTY(EditDefaultsOnly, Category = "Attribute")
    int32 Diamonds;

    UPROPERTY(EditDefaultsOnly, Category = "Attribute")
    int32 Copper;

};



