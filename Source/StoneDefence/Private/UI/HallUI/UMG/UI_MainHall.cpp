// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HallUI/UMG/UI_MainHall.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "UI/HallUI/UMG/UI_HallMenuSystem.h"
#include "SimpleArchives/Public/UI_ArchivesSystem.h"
#include "SimpleTutorial/Public/UI_TutorialSystem.h"
#include "SimpleGameSettings/Public/UI_GameSettingsSystem.h"
#include "Components/SizeBox.h"


template <class T, class UserObject>
UserObject* CreateAssistWidget(T* ThisClass, UClass* AssistClass, USizeBox* WidgetArray)
{
	UserObject* UserObjectElement = nullptr;

	//play animation condition
	if (0)
	{
		//play fade in
	}

	if (WidgetArray->GetChildAt(0))
	{
		if (WidgetArray->GetChildAt(0)->IsA(AssistClass))
		{
			//play fade out
			//UE_LOG(LogTemp, Warning, TEXT("return UserObjectElement"));
			return UserObjectElement;
		}
		else
		{
			WidgetArray->ClearChildren();
		}
	}

	UserObjectElement = CreateWidget<UserObject>(ThisClass->GetWorld(), AssistClass);
	if (UserObjectElement)
	{
		if (WidgetArray->AddChild(UserObjectElement))
		{
			UE_LOG(LogTemp, Warning, TEXT("if"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("else"));
			UserObjectElement->RemoveFromParent();
		}
	}

	return UserObjectElement;
}


void UUI_MainHall::NativeConstruct()
{
	Super::NativeConstruct();

	if (HallMenuSystem)
	{
		//Start game
		{
			FOnButtonClickedEvent Delegate;
			Delegate.AddDynamic(this, &UUI_MainHall::GameStart);
			HallMenuSystem->BindGameStart(Delegate);
		}

		//Secret Territory
		{
			FOnButtonClickedEvent Delegate;
			Delegate.AddDynamic(this, &UUI_MainHall::SecretTerritory);
			HallMenuSystem->BindSecretTerritory(Delegate);
		}

		//History
		{
			FOnButtonClickedEvent Delegate;
			Delegate.AddDynamic(this, &UUI_MainHall::History);
			HallMenuSystem->BindHistory(Delegate);
		}

		//Game Setting
		{
			FOnButtonClickedEvent Delegate;
			Delegate.AddDynamic(this, &UUI_MainHall::GameSettings);
			HallMenuSystem->BindGameSettings(Delegate);
		}

		//TutorialWebsite
		{
			FOnButtonClickedEvent Delegate;
			Delegate.AddDynamic(this, &UUI_MainHall::TutorialWebsite);
			HallMenuSystem->BindTutorialWebsite(Delegate);
		}

		//Browser
		{
			FOnButtonClickedEvent Delegate;
			Delegate.AddDynamic(this, &UUI_MainHall::Browser);
			HallMenuSystem->BindBrowser(Delegate);
		}

		//SpecialContent
		{
			FOnButtonClickedEvent Delegate;
			Delegate.AddDynamic(this, &UUI_MainHall::SpecialContent);
			HallMenuSystem->BindSpecialContent(Delegate);
		}
		
		//QuitGame
		{
			FOnButtonClickedEvent Delegate;
			Delegate.AddDynamic(this, &UUI_MainHall::QuitGame);
			HallMenuSystem->BindQuitGame(Delegate);
		}

	}
}

void UUI_MainHall::GameStart()
{
	UGameplayStatics::OpenLevel(GetWorld(), "SelectLevel");
}

void UUI_MainHall::SecretTerritory()
{

}

void UUI_MainHall::History()
{
	CreateAssistWidget<UUI_MainHall, UUI_ArchivesSystem>(this, ArchivesSystemClass, BoxList);
	UE_LOG(LogTemp, Warning, TEXT("History"));
}

void UUI_MainHall::GameSettings()
{
	CreateAssistWidget<UUI_MainHall, UUI_GameSettingsSystem>(this, GameSettingsClass, BoxList);
}

void UUI_MainHall::TutorialWebsite()
{
	CreateAssistWidget<UUI_MainHall, UUI_TutorialSystem>(this, TutorialSystemClass, BoxList);
}

void UUI_MainHall::Browser()
{
}

void UUI_MainHall::SpecialContent()
{
}

void UUI_MainHall::QuitGame()
{
}