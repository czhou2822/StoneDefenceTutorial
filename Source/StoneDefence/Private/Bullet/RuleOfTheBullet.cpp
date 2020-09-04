// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet/RuleOfTheBullet.h"
#include "Character/Core/RuleOfTheCharacter.h"
#include "Character/Core/RuleOfTheAIController.h"
#include "StoneDefence/StoneDefenceUtils.h"
#include "Components/SceneComponent.h"
#include "Components/SplineComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/DamageType.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "EngineUtils.h"
#include "StoneDefence/Public/Core/GameCore/TowerDefenceGameState.h"
#include "Character/Damage/RuleOfTheDamageType.h"


// Sets default values
ARuleOfTheBullet::ARuleOfTheBullet()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SkillID = INDEX_NONE;

	Spline = nullptr;

	CurrentSplineTime = 0.f;
	SplineOffset = 0.f;

	ChainAttackCount = 3;

	BoxDamage = CreateDefaultSubobject<USphereComponent>(TEXT("BulletBoxDamage"));
	RootBullet = CreateDefaultSubobject<USceneComponent>(TEXT("BulletRootBullet"));
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("BulletProjectileMovement"));

	RootComponent = RootBullet;
	BoxDamage->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	ProjectileMovement->MaxSpeed = 2000.f;
	ProjectileMovement->InitialSpeed = 1600.f;
	ProjectileMovement->ProjectileGravityScale = 0.f;
	ProjectileMovement->UpdatedComponent = BoxDamage;
	BulletType = EBulletType::BULLET_DIRECTLINE;

	InitialLifeSpan = 4.0f;
	SubmissionSkillRequestType = ESubmissionSkillRequestType::AUTO;
}

// Called when the game starts or when spawned
void ARuleOfTheBullet::BeginPlay()
{
	Super::BeginPlay();

	BoxDamage->OnComponentBeginOverlap.AddUniqueDynamic(this, &ARuleOfTheBullet::BeginOverlap);

}

void ARuleOfTheBullet::InitSkill()
{
	if (ARuleOfTheCharacter* InstigatorCharacter = Cast<ARuleOfTheCharacter>(GetInstigator()))
	{
		if (ARuleOfTheAIController* InstigatorController = Cast<ARuleOfTheAIController>(InstigatorCharacter->GetController()))
		{
			if (ARuleOfTheCharacter* TargetCharacter = InstigatorController->Target.Get())
			{
				switch (BulletType)
				{
				case EBulletType::BULLET_DIRECTLINE:
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), OpenFireParticle, GetActorLocation());
					break;
				case EBulletType::BULLET_LINE:
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), OpenFireParticle, GetActorLocation());
					break;
				case EBulletType::BULLET_TRACKLINE_SP:
				{
					ProjectileMovement->StopMovementImmediately();
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), OpenFireParticle, GetActorLocation());

					Spline = NewObject<USplineComponent>(this, TEXT("SplineInstance"));
					Spline->RegisterComponent();
					Spline->SetLocationAtSplinePoint(0, GetActorLocation(), ESplineCoordinateSpace::Local);

					FVector DistanceVector = InstigatorCharacter->GetActorLocation() - TargetCharacter->GetActorLocation();
					FVector Position = (DistanceVector / 2) + TargetCharacter->GetActorLocation();  //mid point
					Position.Y += SplineOffset;
					Position.Z = (DistanceVector.Size() / 2.f) * 0.5f;                              //vertical offset 

					Spline->SetLocationAtSplinePoint(1, Position, ESplineCoordinateSpace::Local);
					Spline->AddSplinePoint(TargetCharacter->GetActorLocation(), ESplineCoordinateSpace::Local);

					break;
				}
				case EBulletType::BULLET_TRACKLINE:
				{
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), OpenFireParticle, GetActorLocation());
					ProjectileMovement->bIsHomingProjectile = true;
					ProjectileMovement->bRotationFollowsVelocity = true;
					ProjectileMovement->HomingAccelerationMagnitude = 4000.f;
					ProjectileMovement->HomingTargetComponent = TargetCharacter->GetHomingPoint();

					break;
				}

				case EBulletType::BULLET_RANGELINE:
				{
					ProjectileMovement->StopMovementImmediately();

					ProjectileMovement->ProjectileGravityScale = 1.f;

					FVector TargetFromOwnerVector = TargetCharacter->GetActorLocation() - GetActorLocation();

					float InTime = (TargetFromOwnerVector.Size() / ProjectileMovement->InitialSpeed);  //air time
					float Y = ProjectileMovement->GetGravityZ() * InTime;
					float X = ProjectileMovement->InitialSpeed * InTime;
					float V = FMath::Sqrt(X * X + Y * Y);

					float CosRadian = FMath::Acos(TargetFromOwnerVector.Size() / V * (InTime * (PI * 0.1f)));
					FRotator Rot = GetActorRotation();
					Rot.Pitch = CosRadian * (180 / PI);
					SetActorRotation(Rot);

					ProjectileMovement->SetVelocityInLocalSpace(FVector(1.0, 0.f, 0.f) * ProjectileMovement->InitialSpeed);
					break;
				}

				case EBulletType::BULLET_RANGE:
				{
					ProjectileMovement->StopMovementImmediately();
					BoxDamage->SetCollisionEnabled(ECollisionEnabled::NoCollision);
					RadialDamage(GetActorLocation(), Cast<ARuleOfTheCharacter>(GetInstigator()));
					break;
				}

				case EBulletType::BULLET_CHAIN:
				{
					ProjectileMovement->StopMovementImmediately();
					BoxDamage->SetCollisionEnabled(ECollisionEnabled::NoCollision);

					UGameplayStatics::SpawnEmitterAttached(DamageParticle, TargetCharacter->GetHomingPoint());

					GetWorld()->GetTimerManager().SetTimer(ChainAttackHandle, this, &ARuleOfTheBullet::ChainAttack, 0.1f);

					SubmissionSkillRequest();

					break;
				}
				case EBulletType::BULLET_NONE:
				{
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), OpenFireParticle, GetActorLocation());
					ProjectileMovement->StopMovementImmediately();
					BoxDamage->SetCollisionEnabled(ECollisionEnabled::NoCollision);
					SubmissionSkillRequest();

				}
				}
			}
		}
	}

}

// Called every frame
void ARuleOfTheBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (ARuleOfTheCharacter* InstigatorCharacter = Cast<ARuleOfTheCharacter>(GetInstigator()))
	{
		if (ARuleOfTheAIController* InstigatorController = Cast<ARuleOfTheAIController>(InstigatorCharacter->GetController()))
		{
			if (ARuleOfTheCharacter* TargetCharacter = InstigatorController->Target.Get())
			{
				switch (BulletType)
				{
					case EBulletType::BULLET_CHAIN:
					{
						TArray<USceneComponent*> SceneComponent;
						RootComponent->GetChildrenComponents(true, SceneComponent);
						for (auto& Tmp : SceneComponent)
						{
							if (UParticleSystemComponent* ParticleSystem = Cast<UParticleSystemComponent>(Tmp))
							{
								ParticleSystem->SetBeamSourcePoint(0, TargetCharacter->GetHomingPoint()->GetComponentLocation(), 0);
								ParticleSystem->SetBeamEndPoint(0, InstigatorCharacter->GetFirePoint()->GetComponentLocation());
							}
						}
						break;
					}

					case EBulletType::BULLET_TRACKLINE_SP:
					{
						if (Spline)
						{
							FVector DistanceVector = InstigatorCharacter->GetActorLocation() - TargetCharacter->GetActorLocation();
							CurrentSplineTime += DeltaTime;

							float Distance = Spline->GetSplineLength() * (CurrentSplineTime / (DistanceVector.Size() / 1000.f));
							FVector Location = Spline->GetWorldLocationAtDistanceAlongSpline(Distance);
							FRotator Rotator = Spline->GetWorldRotationAtDistanceAlongSpline(Distance);

							SetActorLocationAndRotation(Location, Rotator);

							if ((Location - TargetCharacter->GetActorLocation()).Size() <= 100.f)
							{
								FHitResult SweepResult;
								SweepResult.Location = Location;
								BeginOverlap(nullptr, TargetCharacter, nullptr, 0, false, SweepResult);
							}
						}
						break;
					}
				}
				if (!TargetCharacter->IsActive())
				{
					Destroy();
				}

			}
			else
			{
				Destroy();
			}
		}
	}




}



const FSkillData* ARuleOfTheBullet::GetSkillData()
{
	if (ATowerDefenceGameState* InGameState = GetWorld()->GetGameState<ATowerDefenceGameState>())
	{
		return InGameState->GetSkillData(SkillID);
	}
	return nullptr;
}

void ARuleOfTheBullet::SubmissionSkillRequest()
{
	if (SkillID != INDEX_NONE)
	{
		if (ARuleOfTheCharacter* InstigatorCharacter = Cast<ARuleOfTheCharacter>(GetInstigator()))
		{
			if (ATowerDefenceGameState* InGameState = GetWorld()->GetGameState<ATowerDefenceGameState>())
			{
				const FCharacterData& CharacterData = InstigatorCharacter->GetCharacterData();
				if (CharacterData.IsValid())
				{
					if (!InGameState->IsVerificationSkillTemplate(CharacterData, SkillID))    //客户端验证
					{
						//客户端将请求提交到服务器
						InGameState->AddSkillDataTemplateToCharacterData(InstigatorCharacter->GUID, SkillID);

						if (SubmissionSkillRequestType == ESubmissionSkillRequestType::MANUAL)
						{
							//设置类型 这是发生在服务器上
							InGameState->SetSubmissionDataType(InstigatorCharacter->GUID, SkillID, SubmissionSkillRequestType);
						}
					}
				}
			}
		}
	}
}



//bool ARuleOfTheBullet::SetSubmissionDataType(ESubmissionSkillRequestType Type)
//{
//	if (SkillID != INDEX_NONE)
//	{
//		if (ARuleOfTheCharacter* InstigatorCharacter = Cast<ARuleOfTheCharacter>(Instigator))
//		{
//			if (ATowerDefenceGameState* InGameState = GetWorld()->GetGameState<ATowerDefenceGameState>())
//			{
//				return InGameState->SetSubmissionDataType(InstigatorCharacter->GUID, SkillID, Type);
//			}
//		}
//	}
//}

void ARuleOfTheBullet::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (const FSkillData* InData = GetSkillData())
	{
		if (ARuleOfTheCharacter* InstigatorCharacter = Cast<ARuleOfTheCharacter>(GetInstigator()))
		{
			if (ARuleOfTheCharacter* OtherCharacter = Cast<ARuleOfTheCharacter>(OtherActor))
			{
				auto VerifyConsistency = [&]()
				{
					bool bVerifyConsistency = false;
					if (InData->SkillType.TargetType == ESkillTargetType::FRIENDLY_FORCE)
					{
						bVerifyConsistency = InstigatorCharacter->GetTeamType() == OtherCharacter->GetTeamType();
					}
					else if (InData->SkillType.TargetType == ESkillTargetType::ENEMY)
					{
						bVerifyConsistency = InstigatorCharacter->GetTeamType() != OtherCharacter->GetTeamType();
					}
					return bVerifyConsistency;
				};

				if (VerifyConsistency())
				{
					if (InstigatorCharacter->GetTeamType() != OtherCharacter->GetTeamType())
					{
						if (OtherCharacter->IsActive())
						{
							UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DamageParticle, SweepResult.Location);

							switch (BulletType)
							{
								case EBulletType::BULLET_DIRECTLINE:
								case EBulletType::BULLET_LINE:
								case EBulletType::BULLET_TRACKLINE:
								case EBulletType::BULLET_TRACKLINE_SP:
								{
									UClass* RuleOfTheDamage = URuleOfTheDamage::StaticClass();

									if (URuleOfTheDamage* DamageClass = RuleOfTheDamage->GetDefaultObject<URuleOfTheDamage>())
									{
										DamageClass->SkillData = InData;

										UGameplayStatics::ApplyDamage(
											OtherCharacter,
											100.f,
											InstigatorCharacter->GetController(),
											InstigatorCharacter,
											RuleOfTheDamage);

										SubmissionSkillRequest();
									}
									Destroy();
									break;
								}
								case EBulletType::BULLET_RANGELINE:
								{
									RadialDamage(OtherCharacter->GetActorLocation(), InstigatorCharacter);
									Destroy();
									break;
								}
							}
						}
					}
				}
			}
		}
	}
}

void ARuleOfTheBullet::RadialDamage(const FVector& Origin, class ARuleOfTheCharacter* InstigatorCharacter)
{
	if (InstigatorCharacter)
	{
		if (const FSkillData* InData = GetSkillData())
		{

			auto SpawnEffect = [&](ARuleOfTheCharacter* NewCharacter)
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DamageParticle, NewCharacter->GetActorLocation());

				SubmissionSkillRequest();
			};

			TArray<AActor*> IgnoredActors;
			//			TArray<ARuleOfTheCharacter*> TargetActors;
			for (TActorIterator<ARuleOfTheCharacter>it(GetWorld(), ARuleOfTheCharacter::StaticClass()); it; ++it)
			{
				if (ARuleOfTheCharacter* TheCharacter = *it)
				{
					FVector VDistance = TheCharacter->GetActorLocation() - InstigatorCharacter->GetActorLocation();
					if (VDistance.Size() <= InData->AttackRange)
					{
						if (InData->SkillType.TargetType == ESkillTargetType::FRIENDLY_FORCE)
						{
							if (TheCharacter->GetTeamType() == InstigatorCharacter->GetTeamType())
							{
								SpawnEffect(TheCharacter);
							}
							else
							{
								IgnoredActors.Add(TheCharacter);
							}
						}
						else if (InData->SkillType.TargetType == ESkillTargetType::ENEMY)
						{
							if (TheCharacter->GetTeamType() != InstigatorCharacter->GetTeamType())
							{
								SpawnEffect(TheCharacter);
							}
							else
							{
								IgnoredActors.Add(TheCharacter);
							}
						}
					}
				}
			}

			UClass* RuleOfTheDamage = URuleOfTheDamage::StaticClass();

			if (URuleOfTheDamage* DamageClass = RuleOfTheDamage->GetDefaultObject<URuleOfTheDamage>())
			{
				DamageClass->SkillData = InData;
				UGameplayStatics::ApplyRadialDamageWithFalloff(
					GetWorld(),
					100.f, 10.f,
					Origin,
					400.f, 1000.f, 1.f,
					RuleOfTheDamage,
					IgnoredActors,
					GetInstigator(),
					GetInstigator()->GetController(),
					ECollisionChannel::ECC_MAX);
			}
		}
	}
}

//void ARuleOfTheBullet::ResetIteration()
//{
//	BulletType = EBulletType::BULLET_NONE;
//
//	InitSkill();
//
//}

void ARuleOfTheBullet::ChainAttack()
{
	if (ChainAttackHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(ChainAttackHandle);
	}

	//deal damage
	if(const FSkillData* InData = GetSkillData())
	{
		if (ARuleOfTheCharacter* InstigatorCharacter = Cast<ARuleOfTheCharacter>(GetInstigator()))
		{
			if (ARuleOfTheAIController* InstigatorController = Cast<ARuleOfTheAIController>(InstigatorCharacter->GetController()))
			{
				if (ARuleOfTheCharacter* TargetCharacter = InstigatorController->Target.Get())
				{	
					UGameplayStatics::SpawnEmitterAttached(DamageParticle, TargetCharacter->GetHomingPoint());
					UGameplayStatics::SpawnEmitterAttached(OpenFireParticle, InstigatorCharacter->GetHomingPoint());

					UClass* RuleOfTheDamage = URuleOfTheDamage::StaticClass();

					if (URuleOfTheDamage* DamageClass = RuleOfTheDamage->GetDefaultObject<URuleOfTheDamage>())
					{
						DamageClass->SkillData = InData;

						UGameplayStatics::ApplyDamage(
						TargetCharacter,
						100.f,
						InstigatorCharacter->GetController(),
						InstigatorCharacter,
						RuleOfTheDamage);
					}
				}
			}
		}
	}

	ChainAttackCount--;

	if (ChainAttackCount>0)
	{
		GetWorld()->GetTimerManager().SetTimer(ChainAttackHandle, this, &ARuleOfTheBullet::ChainAttack, 0.3f);
	}



}

