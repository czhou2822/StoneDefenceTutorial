// Fill out your copyright notice in the Description page of Project Settings.

#include "Global/GlobalManagement.h"
#include "Global/Blueprint/GlobalConfiguration.h"
#include "Global/Blueprint/GlobalResource.h"
#include "Engine/Blueprint.h"


FGlobalManagement::FGlobalManagement()
	:GlobalResource(nullptr)
	, GlobalConfiguration(nullptr)
{

}

void FGlobalManagement::Constructor(UWorld* InWorld)
{

	if (InWorld)
	{
		if (!GlobalResource)
		{
			if (UBlueprint* BP = Cast<UBlueprint>(StaticLoadObject(UBlueprint::StaticClass(), nullptr, TEXT("Blueprint'/Game/GameData/Global/GlobaoResource_BP.GlobaoResource_BP'"))))
			{
				GlobalResource = NewObject<UGlobalResource>(InWorld, BP->GeneratedClass);
			}
		}

		if (!GlobalConfiguration)
		{
			if (UBlueprint* BP = Cast<UBlueprint>(StaticLoadObject(UBlueprint::StaticClass(), nullptr, TEXT("Blueprint'/Game/GameData/Global/GlobalConfigurationBP.GlobalConfigurationBP'"))))
			{
				GlobalConfiguration = NewObject<UGlobalConfiguration>(InWorld, BP->GeneratedClass);
			}
		}
	}


}

void FGlobalManagement::Destructural()
{

}

const UGlobalResource* FGlobalManagement::GetGlobalResource()
{
	return GlobalResource;
}

const UGlobalConfiguration* FGlobalManagement::GetGlobalConfiguration()
{
	return GlobalConfiguration;
}
