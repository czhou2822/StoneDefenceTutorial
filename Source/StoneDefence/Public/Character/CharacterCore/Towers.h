// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Core/RuleOfTheCharacter.h"
#include "Towers.generated.h"

/**
 * 
 */
UCLASS()
class STONEDEFENCE_API ATowers : public ARuleOfTheCharacter
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttribute", meta = (AllowPrivateAccess = "true"))
	class UParticleSystemComponent* ParticleMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttribute", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* StaticMeshBuilding;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttribute", meta = (AllowPrivateAccess = "true"))
	class UDestructibleComponent* DestructibleMeshBuilding;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BaseAttribute")
	FRotator TowerRotator;

protected:
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	virtual void OnClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);

public:
	ATowers();


	virtual ETeam GetTeamType();


};
