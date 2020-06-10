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

// Sets default values
ARuleOfTheBullet::ARuleOfTheBullet()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
}

// Called when the game starts or when spawned
void ARuleOfTheBullet::BeginPlay()
{
	Super::BeginPlay();

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
					ProjectileMovement->StopMovementImmediately();
					BoxDamage->SetCollisionEnabled(ECollisionEnabled::NoCollision);
					RadialDamage(GetActorLocation(), Cast<ARuleOfTheCharacter>(GetInstigator()));
					break;

				case EBulletType::BULLET_CHAIN:
				{
					ProjectileMovement->StopMovementImmediately();
					BoxDamage->SetCollisionEnabled(ECollisionEnabled::NoCollision);

					UGameplayStatics::SpawnEmitterAttached(DamageParticle, TargetCharacter->GetHomingPoint());

					GetWorld()->GetTimerManager().SetTimer(ChainAttackHandle, this, &ARuleOfTheBullet::ChainAttack, 0.1f);

					break;
				}
				}
			}
		} 
	}



	BoxDamage->OnComponentBeginOverlap.AddUniqueDynamic(this, &ARuleOfTheBullet::BeginOverlap);

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

void ARuleOfTheBullet::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ARuleOfTheCharacter* InstigatorCharacter = Cast<ARuleOfTheCharacter>(GetInstigator()))
	{
		if(ARuleOfTheCharacter* OtherCharacter = Cast<ARuleOfTheCharacter>(OtherActor))
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
							UGameplayStatics::ApplyDamage(
								OtherCharacter, 
								100.f, 
								InstigatorCharacter->GetController(), 
								InstigatorCharacter, 
								UDamageType::StaticClass());

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

void ARuleOfTheBullet::RadialDamage(const FVector& Origin, class ARuleOfTheCharacter* InstigatorCharacter)
{
	if (InstigatorCharacter)
	{
		TArray<AActor*> IgnoredActors;
		//			TArray<ARuleOfTheCharacter*> TargetActors;
		for (TActorIterator<ARuleOfTheCharacter>it(GetWorld(), ARuleOfTheCharacter::StaticClass()); it; ++it)
		{
			if (ARuleOfTheCharacter* TheCharacter = *it)
			{
				FVector VDistance = TheCharacter->GetActorLocation() - InstigatorCharacter->GetActorLocation();
				if (VDistance.Size() <= 1400)
				{
					if (TheCharacter->GetTeamType() == InstigatorCharacter->GetTeamType())
					{
						IgnoredActors.Add(TheCharacter);
					}
					else
					{
						UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DamageParticle, TheCharacter->GetActorLocation());
//						TargetActors.Add(TheCharacter);
					}
				}
			}

		}

		UGameplayStatics::ApplyRadialDamageWithFalloff(
			GetWorld(), 
			100.f, 10.f,
			Origin, 
			400.f, 1000.f, 1.f, 
			UDamageType::StaticClass(), 
			IgnoredActors, 
			GetInstigator(),
			GetInstigator()->GetController(), 
			ECollisionChannel::ECC_MAX);
	}
}

void ARuleOfTheBullet::ChainAttack()
{
	if (ChainAttackHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(ChainAttackHandle);
	}

	//deal damage
	{
		if (ARuleOfTheCharacter* InstigatorCharacter = Cast<ARuleOfTheCharacter>(GetInstigator()))
		{
			if (ARuleOfTheAIController* InstigatorController = Cast<ARuleOfTheAIController>(InstigatorCharacter->GetController()))
			{
				if (ARuleOfTheCharacter* TargetCharacter = InstigatorController->Target.Get())
				{	
					UGameplayStatics::ApplyDamage(
						TargetCharacter,
						100.f,
						InstigatorCharacter->GetController(),
						InstigatorCharacter,
						UDamageType::StaticClass());
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

