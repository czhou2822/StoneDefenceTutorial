#include "StoneDefenceUtils.h"
#include "Interface/Character/RuleCharacter.h"
#include "engine/StaticMesh.h"
#include "RawMesh/Public/RawMesh.h"
#include "SkeletalRenderPublic.h"
#include "Rendering/SkeletalMeshRenderData.h"
#include "Rendering/SkeletalMeshLODRenderData.h"
#include "components/SkeletalMeshComponent.h"
#include "Particles/TypeData/ParticleModuleTypeDataMesh.h"
#include "Particles/ParticleEmitter.h"
#include "particles/ParticleLODLevel.h"
#include "Particles/ParticleSystemComponent.h"
#include "core/gamecore/TowerDefencePlayerState.h"
#include "Engine/StaticMeshActor.h"
#include "Character/Core/RuleOfTheCharacter.h"
#include "engine/World.h"
#include "Components/ArrowComponent.h"
#include "Bullet/RuleOfTheBullet.h"
#include "Bullet/PlayerSkillSlotActor.h"
#include "StoneDefence/Public/Core/GameCore/TowerDefencePlayerController.h"

#if PLATFORM_WINDOWS
#pragma optimize("", off)
#endif


void StoneDefenceUtils::CallUpdateAllClient(UWorld* World, TFunction<void(ATowerDefencePlayerController* MyPlayerController)> InImplement)
{
	if (World)
	{
		for (FConstPlayerControllerIterator It = World->GetPlayerControllerIterator(); It; ++It)
		{
			if (ATowerDefencePlayerController* MyPlayerController = Cast<ATowerDefencePlayerController>(It->Get()))
			{
				InImplement(MyPlayerController);
			}
		}
	}
}

void StoneDefenceUtils::FindRangeTargetRecently(ARuleOfTheCharacter* InOwner, float Range, TArray<ARuleOfTheCharacter*>& Targets)
{
	if (InOwner && Range > 0.0f)
	{
		TArray<ARuleOfTheCharacter*> NewTargets;

		StoneDefenceUtils::GetAllActor(InOwner->GetWorld(), NewTargets);
		for (ARuleOfTheCharacter* Tmp : NewTargets)
		{
			if (InOwner->GetTeamType() != Tmp->GetTeamType())
			{
				if ((InOwner->GetActorLocation() - Tmp->GetActorLocation()).Size() <= Range)
				{
					Targets.Add(Tmp);
				}
			}
		}
	}
}

APlayerSkillSlotActor* StoneDefenceUtils::SpawnPlayerBullet(UWorld* World, int32 SkillID)
{
	if (ATowerDefencePlayerState* InPlayerState = World->GetFirstPlayerController()->GetPlayerState<ATowerDefencePlayerState>())
	{
		if (const FPlayerSkillData* SkillDataState = InPlayerState->GetPlayerSkillDataFormTable(SkillID))
		{
			if (APlayerSkillSlotActor* PlayerSkillSlot = World->SpawnActor<APlayerSkillSlotActor>(SkillDataState->BulletClass, FVector::ZeroVector, FRotator::ZeroRotator))
			{
				return PlayerSkillSlot;
			}
		}
	}

	return nullptr;
}

ARuleOfTheCharacter* StoneDefenceUtils::FindTargetRecently(const TArray<ARuleOfTheCharacter*>& InCharacters, const FVector& Loc)
{
	if (InCharacters.Num())
	{
		float TargetDistance = 99999999;
		int32 Index = INDEX_NONE;

		for (int32 i = 0; i < InCharacters.Num(); i++)
		{
			if (ARuleOfTheCharacter* TowerCharacter = InCharacters[i])
			{
				FVector Location = TowerCharacter->GetActorLocation();
				FVector TmpVector = Location - Loc;
				float Distance = TmpVector.Size();

				if (Distance < TargetDistance && TowerCharacter->IsActive())
				{
					Index = i;
					TargetDistance = Distance;
				}
			}
		}
		if (Index != INDEX_NONE)
		{
			return InCharacters[Index];
		}
	}
	return NULL;
}

ARuleOfTheBullet* StoneDefenceUtils::SpawnBullet(UWorld* World, FGuid CharacterID, UClass* InClass)
{
	TArray<ARuleOfTheCharacter*> Characters;
	StoneDefenceUtils::GetAllActor(World, Characters);

	ARuleOfTheCharacter* Character = nullptr;

	for (auto& Tmp : Characters)
	{
		if (Tmp->GUID == CharacterID)
		{
			return SpawnBullet(World, Tmp, InClass, Tmp->GetFirePoint()->GetComponentLocation(), Tmp->GetFirePoint()->GetComponentRotation());
		}
	}
	return nullptr;
}

ARuleOfTheBullet* StoneDefenceUtils::SpawnBullet(UWorld* World, APawn* NewPawn, UClass* InClass, const FVector& Loc, const FRotator& Rot)
{
	if (World && NewPawn && InClass)
	{
		FTransform Transform;
		Transform.SetLocation(Loc);
		Transform.SetRotation(Rot.Quaternion());

		FActorSpawnParameters ActorSpawnParameter;
		ActorSpawnParameter.Instigator = NewPawn;

		if (ARuleOfTheBullet* Bullet = World->SpawnActor<ARuleOfTheBullet>(InClass, Transform, ActorSpawnParameter))
		{
			return Bullet;
		}
	}
	return nullptr;
}

ARuleOfTheBullet* StoneDefenceUtils::SpawnBullet(UWorld* World, ARuleOfTheCharacter* Owner, const int32 SkillID, const FVector& Loc, const FRotator& Rot)
{
	ARuleOfTheBullet* NewBullet = nullptr;
	if (World)
	{
		if(ATowerDefenceGameState *InGameState = World->GetGameState<ATowerDefenceGameState>())
		{
			if (const FSkillData* InData = InGameState->GetSkillData(SkillID))
			{
				if (ARuleOfTheBullet* Bullet = StoneDefenceUtils::SpawnBullet(World, Owner, InData->BulletClass, Loc, Rot))
				{
					NewBullet = Bullet;
				}
			}
		}
	}
	return NewBullet;
}


void StoneDefenceUtils::Execution(UWorld* World, const FGuid& CharacterID, TFunction<void(ARuleOfTheCharacter* InCharacter)> Code)
{
	if (World)
	{
		TArray<ARuleOfTheCharacter*> Characters;
		StoneDefenceUtils::GetAllActor(World, Characters);
		for (ARuleOfTheCharacter* Tmp : Characters)
		{
			if (Tmp->GUID == CharacterID)
			{
				Code(Tmp);
				break;
			}
		}
	}

}

AStaticMeshActor* StoneDefenceUtils::SpawnTowersDoll(UWorld* World, int32 ID)
{
	AStaticMeshActor* OutActor = NULL;

	if (World)
	{
		if (ATowerDefenceGameState *InGameState = World->GetGameState<ATowerDefenceGameState>())
		{
			const TArray<FCharacterData*> &InData = InGameState->GetTowerDataFormTable();
			

			for (const auto& Tmp : InData)
			{
				if (Tmp->ID == ID)
				{

					UClass* NewClass = Tmp->CharacterBlueprintKey.LoadSynchronous();

					if ( NewClass)
					{
						if (ARuleOfTheCharacter* RuleOfTheCharacter = World->SpawnActor<ARuleOfTheCharacter>(NewClass, FVector::ZeroVector, FRotator::ZeroRotator))
						{
							if (AStaticMeshActor* MeshActor = World->SpawnActor<AStaticMeshActor>(AStaticMeshActor::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator))
							{
								FTransform Transform;
								if (UStaticMesh* InMesh = RuleOfTheCharacter->GetDollMesh(Transform))
								{
									MeshActor->GetStaticMeshComponent()->SetRelativeTransform(Transform);
									MeshActor->SetMobility(EComponentMobility::Movable);
									MeshActor->GetStaticMeshComponent()->SetStaticMesh(InMesh);
									MeshActor->GetStaticMeshComponent()->SetMobility(EComponentMobility::Movable);
									OutActor = MeshActor;
									RuleOfTheCharacter->Destroy();

								}
								else
								{
									MeshActor->Destroy();
									RuleOfTheCharacter->Destroy();
								}
							}
							else
							{
								RuleOfTheCharacter->Destroy();
							}
						}
					}

					break;
				}
			}
		}
	}



	//AStaticMeshActor


	return OutActor;
}

float Expression::GetDamage(IRuleCharacter* Enemy, IRuleCharacter* Owner)
{
	if (Enemy && Owner)
	{
		return Enemy->GetCharacterData().GetAttack() / ((Owner->GetCharacterData().GetArmor() / 100.f) + 1);
	}
	return 0.f;
}

struct FMeshTracker
{
	FMeshTracker()
		:bValidColors(false)
	{
		FMemory::Memset(bValidTexCoords, 0);
	}

	bool bValidTexCoords[MAX_MESH_TEXTURE_COORDS];
	bool bValidColors;
};

void SkeletalMeshToRawMeshes(
	USkeletalMeshComponent* InComponent,
	int32 InOverallMaxLODs,
	const FMatrix& InComponentToWorld,
	FMeshTracker &MeshTracker,
	FRawMesh &RawMesh)
{
	FSkeletalMeshLODInfo& SrcLODInfo = *(InComponent->SkeletalMesh->GetLODInfo(InOverallMaxLODs));

	TArray<FFinalSkinVertex> FinalVertices;
	InComponent->GetCPUSkinnedVertices(FinalVertices, InOverallMaxLODs);
	FSkeletalMeshRenderData& SkeletalMeshRenderData = InComponent->MeshObject->GetSkeletalMeshRenderData();
	FSkeletalMeshLODRenderData& LODData = SkeletalMeshRenderData.LODRenderData[InOverallMaxLODs];
	
	for (int32 VertIndex = 0; VertIndex < FinalVertices.Num(); ++VertIndex)
	{
		RawMesh.VertexPositions.Add(InComponentToWorld.TransformPosition(FinalVertices[VertIndex].Position));
	}

	const uint32 NumTexCoords = FMath::Min(LODData.StaticVertexBuffers.StaticMeshVertexBuffer.GetNumTexCoords(), (uint32)MAX_MESH_TEXTURE_COORDS);
	const int32 NumSections = LODData.RenderSections.Num();

	FRawStaticIndexBuffer16or32Interface& IndexBuffer = *LODData.MultiSizeIndexContainer.GetIndexBuffer();
	for (int32 SectionIndex = 0; SectionIndex < NumSections; SectionIndex++)
	{
		const FSkelMeshRenderSection& SkelMeshSection = LODData.RenderSections[SectionIndex];
		if (InComponent->IsMaterialSectionShown(SkelMeshSection.MaterialIndex, InOverallMaxLODs))
		{
			const int32 NumWedges = SkelMeshSection.NumTriangles * 3;
			for (int32 WedgeIndex = 0; WedgeIndex < NumWedges; WedgeIndex++)
			{
				const int32 VertexIndexForWedge = IndexBuffer.Get(SkelMeshSection.BaseIndex + WedgeIndex);
				RawMesh.WedgeIndices.Add(VertexIndexForWedge);

				const FFinalSkinVertex& SkinnedVertex = FinalVertices[VertexIndexForWedge];
				const FVector TangentX = InComponentToWorld.TransformVector(SkinnedVertex.TangentX.ToFVector());
				const FVector TangentZ = InComponentToWorld.TransformVector(SkinnedVertex.TangentZ.ToFVector());
				const FVector4 UnpackedTangentX = SkinnedVertex.TangentX.ToFVector4();
				const FVector TangentY = (TangentZ ^ TangentX).GetSafeNormal() * UnpackedTangentX.W;
			
				RawMesh.WedgeTangentX.Add(TangentX);
				RawMesh.WedgeTangentY.Add(TangentY);
				RawMesh.WedgeTangentZ.Add(TangentZ);
				for (uint32 TexCoordIndex = 0; TexCoordIndex < MAX_MESH_TEXTURE_COORDS; TexCoordIndex++)
				{
					if (TexCoordIndex >= NumTexCoords)
					{
						RawMesh.WedgeTexCoords[TexCoordIndex].AddDefaulted();
					}
					else
					{
						RawMesh.WedgeTexCoords[TexCoordIndex].Add(LODData.StaticVertexBuffers.StaticMeshVertexBuffer.GetVertexUV(VertexIndexForWedge, TexCoordIndex));
						MeshTracker.bValidTexCoords[TexCoordIndex] = true;
					}
				}

				if (LODData.StaticVertexBuffers.ColorVertexBuffer.IsInitialized())
				{
					RawMesh.WedgeColors.Add(LODData.StaticVertexBuffers.ColorVertexBuffer.VertexColor(VertexIndexForWedge));
					MeshTracker.bValidColors = true;
				}
				else
				{
					RawMesh.WedgeColors.Add(FColor::White);
				}
			}

			int32 MaterialIndex = SkelMeshSection.MaterialIndex;
			if (SrcLODInfo.LODMaterialMap.IsValidIndex(SectionIndex) && SrcLODInfo.LODMaterialMap[SectionIndex] != INDEX_NONE)
			{
				MaterialIndex = FMath::Clamp<int32>(SrcLODInfo.LODMaterialMap[SectionIndex], 0, InComponent->SkeletalMesh->Materials.Num());
			}

			for (uint32 TriIndex = 0; TriIndex < SkelMeshSection.NumTriangles; TriIndex++)
			{
				RawMesh.FaceMaterialIndices.Add(MaterialIndex);
				RawMesh.FaceSmoothingMasks.Add(0);
			}
		}
	}
}

bool IsValidSkeletalMeshComponent(USkeletalMeshComponent* InComponent)
{
	return InComponent && InComponent->MeshObject && InComponent->IsVisible();
}

UStaticMesh* MeshUtils::ParticleSystemComponentToStaticMesh(UParticleSystemComponent* NewParticleComponent)
{
	UStaticMesh* NewStaticMesh = nullptr;
	if (NewParticleComponent->Template && NewParticleComponent->Template->Emitters.Num() > 0)
	{
		for (const UParticleEmitter* Tmp : NewParticleComponent->Template->Emitters)
		{
			if (Tmp->LODLevels[0]->bEnabled)
			{
				if (UParticleModuleTypeDataMesh* MyParticleDataMesh = Cast<UParticleModuleTypeDataMesh>(Tmp->LODLevels[0]->TypeDataModule))
				{
					if (MyParticleDataMesh->Mesh)
					{
						NewStaticMesh = MyParticleDataMesh->Mesh;
						break;
					}
				}
			}
		}
	}

	return NewStaticMesh;
}

UStaticMesh * MeshUtils::SkeletalMeshComponentToStaticMesh(USkeletalMeshComponent* SkeletalMeshComponent)
{
	UStaticMesh* StaticMesh = nullptr;

	if (UWorld *World = SkeletalMeshComponent->GetWorld())
	{
		FRawMesh RawMesh;
		FMeshTracker MeshTracker;
		int32 OverallMaxLODs = 0;

		const FTransform& InRootTransform = FTransform::Identity;
		FMatrix WorldToRoot = InRootTransform.ToMatrixWithScale().Inverse();
		FMatrix ComponentToWorld = SkeletalMeshComponent->GetComponentTransform().ToMatrixWithScale() * WorldToRoot;

		if (IsValidSkeletalMeshComponent(SkeletalMeshComponent))
		{
			SkeletalMeshToRawMeshes(SkeletalMeshComponent, OverallMaxLODs, ComponentToWorld, MeshTracker, RawMesh);
		}
		uint32 MaxInUseTextureCoordinate = 0;

		if (!MeshTracker.bValidColors)
		{
			RawMesh.WedgeColors.Empty();
		}

		for (uint32 TexCoordIndex = 0; TexCoordIndex < MAX_MESH_TEXTURE_COORDS; TexCoordIndex++)
		{
			if (!MeshTracker.bValidTexCoords[TexCoordIndex])
			{
				RawMesh.WedgeTexCoords[TexCoordIndex].Empty();
			}
			else
			{
				MaxInUseTextureCoordinate = FMath::Max(MaxInUseTextureCoordinate, TexCoordIndex);
			}
		}

		if (RawMesh.IsValidOrFixable())
		{
			FString MeshName = FGuid::NewGuid().ToString();
			StaticMesh = NewObject<UStaticMesh>(World, *MeshName, RF_Transient | RF_Standalone);
			StaticMesh->InitResources();

			StaticMesh->LightingGuid = FGuid::NewGuid();

			const uint32 LightMapIndex = FMath::Min(MaxInUseTextureCoordinate + 1, (uint32)8 - 1);

			FStaticMeshSourceModel& SrcModel = StaticMesh->AddSourceModel();
			SrcModel.BuildSettings.bRecomputeNormals = false;
			SrcModel.BuildSettings.bRecomputeTangents = false;
			SrcModel.BuildSettings.bRemoveDegenerates = true;
			SrcModel.BuildSettings.bUseHighPrecisionTangentBasis = false;
			SrcModel.BuildSettings.bUseFullPrecisionUVs = false;
			SrcModel.BuildSettings.bGenerateLightmapUVs = true;
			SrcModel.BuildSettings.SrcLightmapIndex = 0;
			SrcModel.BuildSettings.DstLightmapIndex = LightMapIndex;
			SrcModel.SaveRawMesh(RawMesh);

			for (const UMaterialInterface* Material : SkeletalMeshComponent->GetMaterials())
			{
				StaticMesh->StaticMaterials.Add(FStaticMaterial(const_cast<UMaterialInterface*>(Material)));
			}

			StaticMesh->ImportVersion = EImportStaticMeshVersion::LastVersion;
			StaticMesh->LightMapCoordinateIndex = LightMapIndex;

			TArray<int32> UniqueMaterialIndices;
			for (int32 MaterialIndex : RawMesh.FaceMaterialIndices)
			{
				UniqueMaterialIndices.AddUnique(MaterialIndex);
			}

			for (int32 i = 0; i < UniqueMaterialIndices.Num(); i++)
			{
				StaticMesh->GetSectionInfoMap().Set(0, i, FMeshSectionInfo(UniqueMaterialIndices[i]));
			}
			StaticMesh->GetOriginalSectionInfoMap().CopyFrom(StaticMesh->GetSectionInfoMap());

			StaticMesh->Build(false);
		}
	}

	return StaticMesh;
}








#if PLATFORM_WINDOWS
#pragma optimize("", on)
#endif
