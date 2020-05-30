// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "SimpleScreenLoading.h"
#include "UObject/UObjectGlobals.h"
#include "SimpleScreenLoading/Public/ScreenLoading.h"
#include "Runtime/MoviePlayer/Public/MoviePlayer.h"

//#define LOCTEXT_NAMESPACE "FSimpleScreenLoadingModule"

void FSimpleScreenLoadingModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module


	SetupScreenLoading();

}

void FSimpleScreenLoadingModule::SetupScreenLoading()
{
	FCoreUObjectDelegates::PreLoadMap.AddRaw(this, &FSimpleScreenLoadingModule::BeginLoadingScreen);
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddRaw(this, &FSimpleScreenLoadingModule::EndLoadingScreen);
}

void FSimpleScreenLoadingModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

void FSimpleScreenLoadingModule::BeginLoadingScreen(const FString& MapName)
{
	FLoadingScreenAttributes LoadingScreenArg;
	LoadingScreenArg.bAutoCompleteWhenLoadingCompletes = false;
	LoadingScreenArg.bMoviesAreSkippable = true;
	LoadingScreenArg.bWaitForManualStop = false;
	LoadingScreenArg.PlaybackType = EMoviePlaybackType::MT_LoadingLoop;
	LoadingScreenArg.WidgetLoadingScreen = SNew(SScreenLoading, MapName);

	GetMoviePlayer()->SetupLoadingScreen(LoadingScreenArg);
	GetMoviePlayer()->PlayMovie();
}

void FSimpleScreenLoadingModule::EndLoadingScreen(UWorld* MapName)
{
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSimpleScreenLoadingModule, SimpleScreenLoading)