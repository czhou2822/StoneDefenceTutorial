// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StoneDefence/StoneDefenceType.h"
#include "GameFramework/Character.h"
#include "Interface/Character/RuleCharacter.h"
#include "Core/GameCore/TowerDefencePlayerController.h"
#include "Core/GameCore/TowerDefenceGameState.h"
#include "Core/GameCore/TowerDefencePlayerState.h"

#include "RuleOfTheCharacter.generated.h"

UCLASS()
class STONEDEFENCE_API ARuleOfTheCharacter : public ACharacter, public IRuleCharacter
{
	GENERATED_BODY()
private:


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttribute", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* HomingPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttribute", meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* Widget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttribute", meta = (AllowPrivateAccess = "true"))
	class UArrowComponent* OpenFirePoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttribute", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* TraceShowCharacterInformation;


#if WITH_EDITOR
	FCharacterData NULLData;
#endif	


public:

	UPROPERTY(EditDefaultsOnly, Category = Death)
		float DelayDeath;

	UPROPERTY(EditDefaultsOnly, Category = UI)
	TSubclassOf<class ADrawText> DrawTextClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CharacterAttribute")
	bool bAttack;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UI)
	FGuid GUID;


	UPROPERTY(EditDefaultsOnly, Category = Type)
	TEnumAsByte<EGameCharacterType::Type> CharacterType;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION()
	virtual void OnClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);

public:	
	// Sets default values for this character's properties
	ARuleOfTheCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual EGameCharacterType::Type GetCharacterType();

	virtual bool IsDead();

	virtual float GetHealth();

	virtual float GetMaxHealth();

	virtual ETeam GetTeamType();

	void UpdateUI();

	virtual FCharacterData& GetCharacterData();

	UFUNCTION(Blueprintable, BlueprintPure, Category = "Towers|Test")
	UStaticMesh* GetDollMesh(FTransform& Transform);

	UFUNCTION(Blueprintable, BlueprintPure, Category = "Towers|Attribute")
	bool IsActive() { return !IsDead(); }

	UFUNCTION(BlueprintImplementableEvent)
	void AttackBegin();

	UFUNCTION(BlueprintImplementableEvent)
	void AttackEnd();

	UFUNCTION(BlueprintImplementableEvent)
	void CharacterDeath();

	UFUNCTION(BlueprintImplementableEvent)
	void AnimTag();

	FORCEINLINE ATowerDefencePlayerController* GetGameController() { return GetWorld() ? GetWorld()->GetFirstPlayerController<ATowerDefencePlayerController>() : NULL; }

	FORCEINLINE ATowerDefenceGameState* GetGameState() { return GetWorld() ? GetWorld()->GetGameState<ATowerDefenceGameState>() : NULL; }

	FORCEINLINE ATowerDefencePlayerState* GetPlayerState() { return GetGameController()->GetPlayerState<ATowerDefencePlayerState>(); }

	FORCEINLINE USceneComponent* GetHomingPoint() const { return HomingPoint; }

	FORCEINLINE UArrowComponent* GetFirePoint() const { return OpenFirePoint; }



};
