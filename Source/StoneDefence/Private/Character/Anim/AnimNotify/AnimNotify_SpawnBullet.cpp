// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Anim/AnimNotify/AnimNotify_SpawnBullet.h"
#include "Bullet/RuleOfTheBullet.h"
#include "Engine/World.h"
#include "Components/ArrowComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Character/Core/RuleOfTheCharacter.h"

UAnimNotify_SpawnBullet::UAnimNotify_SpawnBullet()
	:Super()
{
#if WITH_EDITORONLY_DATA
	InSocketName = TEXT("OpenFire");
	NotifyColor = FColor(196, 142, 255, 255);
#endif
}

FString UAnimNotify_SpawnBullet::GetNotifyName_Implementation() const
{
	if (BulletClass)
	{
		return BulletClass->GetName();
	}
	else
	{
		return Super::GetNotifyName_Implementation();
	}
	
}

void UAnimNotify_SpawnBullet::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
#if WITH_EDITOR
	FVector ComponentLocation = MeshComp->GetSocketLocation(InSocketName);
	FRotator ComponentRotation = MeshComp->GetSocketRotation(InSocketName);
#else
	FVector ComponentLocation = Character->GetFirePoint()->GetComponentLocation();
	FRotator ComponentRotation = Character->GetFirePoint()->GetComponentRotation();

#endif
	if (AActor* Character = Cast<AActor>(MeshComp->GetOuter()))

	{
		FTransform Transform;
		Transform.SetLocation(ComponentLocation);
		Transform.SetRotation(ComponentRotation.Quaternion());

		FActorSpawnParameters ActorSpawnParameter;
		ActorSpawnParameter.Instigator = Cast<APawn>(Character);

		if (ARuleOfTheBullet* Bullet = Character->GetWorld()->SpawnActor<ARuleOfTheBullet>(BulletClass, Transform, ActorSpawnParameter))
		{

		}
	}

}