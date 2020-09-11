#include "SimpleGameSettings/Public/Core/SimpleGameUserSettings.h"
#include "Internationalization/Internationalization.h"
#include "Internationalization/Culture.h"


void USimpleGameUserSettings::SetCurrentLanguage(const FString& NewLanguage)
{
	if (NewLanguage == "English" || NewLanguage == "en")
	{
		FInternationalization::Get().SetCurrentCulture("en");
	}
	else if(NewLanguage == "Chinese" || NewLanguage == "zh" || NewLanguage == "zh-CN")
	{
		FInternationalization::Get().SetCurrentCulture("zh");
	}
}

USimpleGameUserSettings* USimpleGameUserSettings::GetSimpleGameUserSettings()
{
//	GEngine->GetGameUserSettings();
	return GEngine != NULL ? (Cast<USimpleGameUserSettings>(GEngine->GetGameUserSettings())) : NULL;
}

FString USimpleGameUserSettings::GetCurrentLanguageType()
{
	if (FInternationalization::Get().GetCurrentCulture().Get().GetName() == "en")
	{
		return "English";
	}
	else if ((FInternationalization::Get().GetCurrentCulture().Get().GetName() == "zh") || (FInternationalization::Get().GetCurrentCulture().Get().GetName() == "zh-CN"))
	{
		return "Chinese";
	}

	return "English";

}


