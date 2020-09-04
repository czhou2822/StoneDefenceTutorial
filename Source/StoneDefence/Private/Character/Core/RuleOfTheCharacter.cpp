// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Core/RuleOfTheCharacter.h"
#include "Actor/DrawText.h"
#include "Bullet/RuleOfTheBullet.h"
#include "Components/SceneComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Particles/ParticleEmitter.h"
#include "particles/ParticleSystemComponent.h"
#include "Particles/TypeData/ParticleModuleTypeDataMesh.h"
#include "Particles/ParticleLODLevel.h"
#include "UI/Character/UI_Health.h"
#include "StoneDefence/StoneDefenceUtils.h"
#include "StoneDefence/StoneDefenceMacro.h"
#include "Character/Damage/RuleOfTheDamageType.h"

#if PLATFORM_WINDOWS
#pragma optimize("", off)
#endif

// Sets default values
ARuleOfTheCharacter::ARuleOfTheCharacter()
	:bAttack(false)
	, DelayDeath(10.f)
{
	GUID = FGuid::NewGuid();

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	HomingPoint = CreateDefaultSubobject<USceneComponent>(TEXT("HomingPoint"));
	Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	OpenFirePoint = CreateDefaultSubobject<UArrowComponent>(TEXT("SpawnPoint"));
	TraceShowCharacterInformation = CreateDefaultSubobject<UBoxComponent>(TEXT("TraceBox"));

	HomingPoint->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	Widget->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	OpenFirePoint->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	TraceShowCharacterInformation->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	TraceShowCharacterInformation->SetCollisionProfileName("Scanning");
	TraceShowCharacterInformation->SetBoxExtent(FVector(38,38,100));

	CharacterType = EGameCharacterType::MINI;

}

// Called when the game starts or when spawned
void ARuleOfTheCharacter::BeginPlay()
{
	Super::BeginPlay();

	TraceShowCharacterInformation->OnClicked.AddDynamic(this, &ARuleOfTheCharacter::OnClicked);

	if (!GetController())
	{
		SpawnDefaultController();
	}
	UpdateUI();
}

float ARuleOfTheCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	float DamageValue = 0.f;

	if (URuleOfTheDamage* DamageClass = DamageEvent.DamageTypeClass->GetDefaultObject<URuleOfTheDamage>())
	{
		if (const FSkillData* SkillData = DamageClass->SkillData)
		{
			auto DrawGameText = [&](ARuleOfTheCharacter *InOwner, const TCHAR *InText, float InDamageValue, FLinearColor InColor)
			{
				//draw damage
				if (DrawTextClass)
				{
					if (ADrawText* MyValueText = GetWorld()->SpawnActor<ADrawText>(DrawTextClass, GetActorLocation(), FRotator::ZeroRotator))
					{
						FString DamageText = FString::Printf(InText, InDamageValue);
						MyValueText->SetTextBlock(DamageText, InColor, InDamageValue / InOwner->GetCharacterData().GetMaxHealth());
					}
				}
			};

			if (SkillData->SkillType.SkillEffectType == ESkillEffectType::SUBTRACT)
			{
				DamageValue = Expression::GetDamage(Cast<ARuleOfTheCharacter>(DamageCauser), this);

				if (DamageValue)
				{
					GetCharacterData().Health -= DamageValue;

					//绘制受伤字体
					DrawGameText(this, TEXT("-%0.f"), DamageValue, FLinearColor::Red);
				}

				if (SkillData->AttackSpeed)
				{
					GetCharacterData().AttackSpeed -= SkillData->AttackSpeed;
					//绘制受伤字体
					DrawGameText(this, TEXT("-%0.f"), SkillData->AttackSpeed, FLinearColor::Black);
				}
				if (SkillData->PhysicalAttack)
				{
					GetCharacterData().PhysicalAttack -= SkillData->PhysicalAttack;
					//绘制受伤字体
					DrawGameText(this, TEXT("-%0.f"), SkillData->PhysicalAttack, FLinearColor::Black);
				}
				if (SkillData->Armor)
				{
					GetCharacterData().Armor -= SkillData->Armor;
					//绘制受伤字体
					DrawGameText(this, TEXT("-%0.f"), SkillData->Armor, FLinearColor::Black);
				}


			}
					
			else if (SkillData->SkillType.SkillEffectType == ESkillEffectType::ADD)
			{
				if (SkillData->PhysicalAttack)
				{
					GetCharacterData().PhysicalAttack += SkillData->PhysicalAttack;
					//绘制受伤字体
					DrawGameText(this, TEXT("-%0.f"), SkillData->PhysicalAttack, FLinearColor::Blue);
				}

				if (SkillData->Armor)
				{
					GetCharacterData().Armor += SkillData->Armor;
					//绘制受伤字体
					DrawGameText(this, TEXT("-%0.f"), SkillData->Armor, FLinearColor::White);
				}

				if (SkillData->AttackSpeed)
				{
					GetCharacterData().AttackSpeed += SkillData->AttackSpeed;
					//绘制受伤字体
					DrawGameText(this, TEXT("-%0.f"), SkillData->AttackSpeed, FLinearColor::White);
				}

				if (SkillData->Health)
				{
					GetCharacterData().Health += SkillData->Health;
					if (GetCharacterData().Health > GetCharacterData().MaxHealth)
					{
						GetCharacterData().Health = GetCharacterData().MaxHealth;
					}

					//绘制受伤字体
					DrawGameText(this, TEXT("-%0.f"), SkillData->AttackSpeed, FLinearColor::Green);
				}
			}
			//死亡判断
			if (!IsActive())
			{
				CharacterDeath();
				//get gold
				if (GetPlayerState()->GetPlayerData().Team == GetTeamType())
				{
					GetPlayerState()->GetPlayerData().GameGold += GetCharacterData().Gold;
				}


				GetCharacterData().Health = 0.0f;
				SetLifeSpan(DelayDeath);


				Widget->SetVisibility(false);
		


				if (ARuleOfTheCharacter* CauserCharacter = Cast<ARuleOfTheCharacter>(DamageCauser))
				{
					if (CauserCharacter->IsActive())
					{
						if (CauserCharacter->GetCharacterData().UpdateEP(GetCharacterData().AddEmpiricalValue))
						{
							//level sfx
						}

						DrawGameText(CauserCharacter, TEXT("+EP -%0.f"), GetCharacterData().AddEmpiricalValue, FLinearColor::Yellow);
					}
					TArray<ARuleOfTheCharacter*> EnemyCharacters;
					StoneDefenceUtils::FindRangeTargetRecently(this, 100.f, EnemyCharacters);
					for (ARuleOfTheCharacter* InEnemy : EnemyCharacters)
					{
						if (InEnemy != CauserCharacter)
						{
							if (InEnemy->IsActive())
							{
								if (InEnemy->GetCharacterData().UpdateEP(GetCharacterData().AddEmpiricalValue * 0.3f))
								{
							
								}

								DrawGameText(InEnemy, TEXT("+EP -%0.f"), GetCharacterData().AddEmpiricalValue, FLinearColor::Yellow);

							}
						}
					}
				}
				GetGameState()->RemoveCharacterData(GUID);
			}
			else
			{
				SubmissionSkillRequest(SkillData->ID);
			}
		}
	}

	return DamageValue;
}

void ARuleOfTheCharacter::OnClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	//SD_print_s("Hello");
}

void ARuleOfTheCharacter::RemoveSkillSlot_Client(const FGuid& SlotID)
{
	if (UUI_Health* HealthUI = Cast<UUI_Health>(Widget->GetUserWidgetObject()))
	{
		HealthUI->RemoveSkillSlot(SlotID);
	}
}

void ARuleOfTheCharacter::AddSkillSlot_Client(const FGuid& SlotID)
{
	if (UUI_Health* HealthUI = Cast<UUI_Health>(Widget->GetUserWidgetObject()))
	{
		HealthUI->AddSkillSlot(SlotID);
	}
}

bool ARuleOfTheCharacter::IsDead()
{
	return GetHealth() <= 0.f;
}

float ARuleOfTheCharacter::GetHealth()
{
	return GetCharacterData().Health;
}

float ARuleOfTheCharacter::GetMaxHealth()
{
	return GetCharacterData().GetMaxHealth();
}

ETeam ARuleOfTheCharacter::GetTeamType()
{
	return GetCharacterData().Team;
}

void ARuleOfTheCharacter::UpdateUI()
{
	if (Widget)
	{
		if (GetCharacterData().IsValid())
		{
			if (UUI_Health* HealthUI = Cast<UUI_Health>(Widget->GetUserWidgetObject()))
			{
				HealthUI->SetTitle(GetCharacterData().Name.ToString());
				HealthUI->SetHealth(GetHealth() / GetMaxHealth());
			}
		}

	}

}

void ARuleOfTheCharacter::InitSkill()
{
	for (auto& Tmp : SkillIDs)
	{
		if (ARuleOfTheBullet* Bullet = StoneDefenceUtils::SpawnBullet(GetWorld(), this, Tmp, OpenFirePoint->GetComponentLocation(), OpenFirePoint->GetComponentRotation()))
		{
			Bullet->InitSkill();
		}
	}
}

void ARuleOfTheCharacter::UpdateSkill(int32 SkillID)
{
	for (auto& Tmp : SkillIDs)
	{
		if (Tmp == SkillID)
		{
			if (ARuleOfTheBullet* Bullet = StoneDefenceUtils::SpawnBullet(GetWorld(), this, Tmp, OpenFirePoint->GetComponentLocation(), OpenFirePoint->GetComponentRotation()))
			{
				Bullet->InitSkill();
			}
			break;
		}
	}
}





void ARuleOfTheCharacter::SubmissionSkillRequest(int32 SkillID)
{
	if (!GetGameState()->IsVerificationSkill(GUID, SkillID))
	{
		GetGameState()->AddSkill(GUID, SkillID);
	}
}

FCharacterData& ARuleOfTheCharacter::GetCharacterData()
{
#if WITH_EDITOR
	if (GetGameState())
	{
		return GetGameState()->GetCharacterData(GUID);
	}
	return NULLData;

#else
	return GetGameState()->GetCharacterData(GUID);
#endif
}

void ARuleOfTheCharacter::ResetGUID()
{
	GUID = FGuid::NewGuid();
}

UStaticMesh* ARuleOfTheCharacter::GetDollMesh(FTransform& Transform)
{
	TArray<USceneComponent*> SceneComponent;
	RootComponent->GetChildrenComponents(true, SceneComponent);
	for (auto& Tmp : SceneComponent)
	{
		if (UStaticMeshComponent* NewMeshComponent = Cast<UStaticMeshComponent>(Tmp))
		{
			if (NewMeshComponent->GetStaticMesh())
			{
				Transform = NewMeshComponent->GetComponentTransform();
				return NewMeshComponent->GetStaticMesh();
			}
		}
		else if (UParticleSystemComponent* NewParticleSystemComponent = Cast<UParticleSystemComponent>(Tmp))
		{
			if (UStaticMesh* NewMesh = MeshUtils::ParticleSystemComponentToStaticMesh(NewParticleSystemComponent))
			{
				Transform = NewParticleSystemComponent->GetComponentTransform();
				return NewMesh;
			}
		}
		else if (USkeletalMeshComponent* NewSkeletalMeshComponent = Cast<USkeletalMeshComponent>(Tmp))
		{
			Transform = NewSkeletalMeshComponent->GetComponentTransform();
			NewSkeletalMeshComponent->SetRelativeTransform(FTransform::Identity);
			NewSkeletalMeshComponent->SetWorldTransform(FTransform::Identity);
			NewSkeletalMeshComponent->SetRelativeRotation(Transform.GetRotation());

			if (UStaticMesh* NewMesh = MeshUtils::SkeletalMeshComponentToStaticMesh(NewSkeletalMeshComponent))
			{
				return NewMesh;
			}
			/*break;*/
		}
	}
	return NULL;
}

// Called every frame
void ARuleOfTheCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateUI();

}

EGameCharacterType::Type ARuleOfTheCharacter::GetCharacterType()
{
	return CharacterType;
}



#if PLATFORM_WINDOWS
#pragma optimize("", on)
#endif