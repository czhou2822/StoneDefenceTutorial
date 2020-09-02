// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterCore/Towers.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Global/UI_Data.h"
#include "DestructibleComponent.h"



ATowers::ATowers()
{
	ParticleMesh = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleMesh"));
	StaticMeshBuilding = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RangeBuilding"));
	DestructibleMeshBuilding = CreateDefaultSubobject<UDestructibleComponent>(TEXT("Substitute"));

	StaticMeshBuilding->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	DestructibleMeshBuilding->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ParticleMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

void ATowers::RegisterTeam()
{
	GetCharacterData().Team = ETeam::RED;

}








float ATowers::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	return 0.0f;
}

void ATowers::OnClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	Super::OnClicked(TouchedComponent, ButtonPressed);

	if (ClickedTargetTower == nullptr)
	{
		ClickedTargetTower = this;
	}
	else
	{
		ClickedTargetTower = nullptr;
	}
}


