// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StoneDefence/StoneDefenceType.h"
#include "Data/SkillData.h"
#include "RuleOfTheBullet.generated.h"


class ARuleOfTheCharacter;
class USplineComponent;

UCLASS()
class STONEDEFENCE_API ARuleOfTheBullet : public AActor
{
	GENERATED_BODY()

private:


	UPROPERTY()
	float CurrentSplineTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttribute", meta = (AllowPrivateAccess = "true"))
	class USphereComponent* BoxDamage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttribute", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* RootBullet;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttribute", meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY()
	class USplineComponent* Spline;

	FTimerHandle ChainAttackHandle;

	UPROPERTY()
	uint8 ChainAttackCount;


public:	
	UPROPERTY(EditDefaultsOnly, Category = "Bullet")
	int32 SkillID;

	UPROPERTY(EditDefaultsOnly, Category = "Bullet")
	TEnumAsByte<EBulletType> BulletType;

	UPROPERTY(EditDefaultsOnly, Category = "Bullet")
	UParticleSystem* DamageParticle;

	UPROPERTY(EditDefaultsOnly, Category = "Bullet")
	UParticleSystem* OpenFireParticle;

	UPROPERTY(EditDefaultsOnly, Category = "Bullet track line sp")
	float SplineOffset;
	
	UPROPERTY()
	ESubmissionSkillRequestType SubmissionSkillRequestType;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void ChainAttack();

	void RadialDamage(const FVector& Origin, class ARuleOfTheCharacter* InstigatorCharacter);

	//void ResetIteration();

public:	
	// Sets default values for this actor's properties
	ARuleOfTheBullet();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void InitSkill();

	const FSkillData* GetSkillData();

	UFUNCTION(BlueprintCallable, Category = "Add Skill Request")
	void SubmissionSkillRequest();


};
