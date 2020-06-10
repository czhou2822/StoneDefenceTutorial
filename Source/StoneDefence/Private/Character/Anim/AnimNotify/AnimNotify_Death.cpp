// Fill out your copyright notice in the Description page of Project Settings.



#include "Character/Anim/AnimNotify/AnimNotify_Death.h"
#if WITH_EDITOR
//Persona
//#include "Persona/Public/AnimationEditorPreviewActor.h"
#include "AnimationEditorPreviewActor.h"
#endif
#include "Components/SkeletalMeshComponent.h"

UAnimNotify_Death::UAnimNotify_Death()
	:Super()
{

#if WITH_EDITORONLY_DATA
	NotifyColor = FColor(0, 0, 0, 255);
#endif

}

void UAnimNotify_Death::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
#if WITH_EDITOR
	AAnimationEditorPreviewActor* Character = Cast<AAnimationEditorPreviewActor>(MeshComp->GetOuter());
	if (!Character)
	{
		if (AActor* CharacterActor = Cast<AActor>(MeshComp->GetOuter()))
		{
			CharacterActor->Destroy();
		}
	}
#else
	if (AActor* Character = Cast<AActor>(MeshComp->GetOuter()))
	{
		Character->Destroy();
	}
#endif
}