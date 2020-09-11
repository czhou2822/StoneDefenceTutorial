// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Bullet/RuleOfTheBullet.h"
#include "EngineUtils.h"

class USizeBox;
class ARuleOfTheCharacter;
class IRuleCharacter;
class UStaticMesh;
class AStaticMeshActor;
class USkeletalMeshComponent;
class UWorld;
class ARuleOfTheBullet;
class APlayerSkillSlotActor;
class ATowerDefencePlayerController;
class ASceneCapture2D;

namespace StoneDefenceUtils
{
	void CallUpdateAllClient(UWorld *World, TFunction<void(ATowerDefencePlayerController* MyPlayerController)> InImplement);

	void FindRangeTargetRecently(ARuleOfTheCharacter* InOwner, float Range, TArray<ARuleOfTheCharacter*>& Targets);

	APlayerSkillSlotActor* SpawnPlayerBullet(UWorld* World, int32 SkillID);

	ARuleOfTheCharacter* FindTargetRecently(const TArray<ARuleOfTheCharacter*>& InCharacters, const FVector& Loc);

	ARuleOfTheBullet* SpawnBullet(UWorld* World, FGuid CharacterID, UClass* InClass);

	ARuleOfTheBullet* SpawnBullet(UWorld* World, APawn *NewPawn, UClass *InClass, const FVector &Loc, const FRotator &Rot);

	ARuleOfTheBullet* SpawnBullet(UWorld* World, ARuleOfTheCharacter* Owner, const int32 SkillID, const FVector& Loc, const FRotator& Rot);


	template<class A, class B>
	void GetAllActor(UWorld* World, TArray<B*>& Array)
	{
		for (TActorIterator<A>It(World, A::StaticClass()); It; ++It)
		{
			if (B* Tmp = Cast<A>(*It))
			{
				Array.Add(Tmp);
			}
		}
	}



	template<class Type>
	void GetAllActor(UWorld *World, TArray<Type*> &Array)
	{
		for (TActorIterator<Type>It(World, Type::StaticClass()); It; ++It)
		{
			Array.Add(*It);
		}
	}



	template<class Type>
	TArray<Type*> GetAllActor(UWorld* World)
	{
		TArray<Type*> Array;
		for (TActorIterator<Type>It(World, Type::StaticClass()); It; ++It)
		{
			if (Type* A = Cast<Type>(*It))
			{
				Array.Add(A);
			}
		}
		return Array;
	}


	void Execution(UWorld* World, const FGuid& CharacterID, TFunction<void(ARuleOfTheCharacter* InCharacter)> Code);


	AStaticMeshActor* SpawnTowersDoll(UWorld* World, int32 ID);



}

namespace Expression
{
	float GetDamage(IRuleCharacter* Enemy, IRuleCharacter* Owner);
}

namespace MeshUtils
{

	UStaticMesh* ParticleSystemComponentToStaticMesh(UParticleSystemComponent* NewParticleComponent);
	UStaticMesh* SkeletalMeshComponentToStaticMesh(USkeletalMeshComponent *SkeletalMeshComponent);


}


namespace RenderingUtils
{
	struct FScreenShot
	{
		FScreenShot(
			int32 InWidth,
			int32 InHeight,
			UTexture2D*& InTexture,
			UObject* InOuter,
			int32 InImageQuality = 80,
			bool bInShowUI = false,
			bool bAddFilenameSuffix = true);

		FString& GetFilename() { return Filename; }
	protected:
		void OnScreenshotCapturedInternal(int32 SrcWidth, int32 SrcHeight, const TArray<FColor>& OrigBitmap);
	private:
		UTexture2D*& Texture;
		FDelegateHandle ScreenShotDelegateHandle;
		int32 ScaledWidth;
		int32 ScaledHeight;
		int32 ImageQuality;
		UObject* Outer;
		FString Filename;
	};

	ASceneCapture2D* SpawnSceneCapture2D(UWorld* World, UClass* SceneCaptureClass, FMapSize& MapSize, float Life = 0.f);
}


