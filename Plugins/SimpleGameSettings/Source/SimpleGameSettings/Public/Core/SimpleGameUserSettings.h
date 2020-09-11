#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "SimpleGameUserSettings.generated.h"


/**
 *
 */
UCLASS()
class SIMPLEGAMESETTINGS_API USimpleGameUserSettings : public UGameUserSettings
{
	GENERATED_BODY()


public:
	UPROPERTY(config)
	bool bSupportPhysX;

public:
	void SetCurrentLanguage(const FString& NewLanguage);

	static USimpleGameUserSettings* GetSimpleGameUserSettings();

	FString GetCurrentLanguageType();
};