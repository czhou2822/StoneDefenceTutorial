// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/CharacterCore/Monsters.h"
#include "UI/Core/UI_Data.h"
#include "GameFramework/CharacterMovementComponent.h"

void AMonsters::BeginPlay()
{
	Super::BeginPlay();
}

void AMonsters::OnClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	Super::OnClicked(TouchedComponent, ButtonPressed);
	if (ClickedTargetMonster == nullptr)
	{
		ClickedTargetMonster = this;
	}
	else
	{
		ClickedTargetMonster = nullptr;
	}

}


void AMonsters::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//GetCharacterMovement()->MaxWalkSpeed = GetCharacterData().GetWalkSpeed();

}

void AMonsters::RegisterTeam()
{
	GetCharacterData().Team = ETeam::BLUE;
}


