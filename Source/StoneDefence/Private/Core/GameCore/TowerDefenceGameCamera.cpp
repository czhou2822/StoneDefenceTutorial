// Fill out your copyright notice in the Description page of Project Settings.

#include "StoneDefence/Public/Core/GameCore/TowerDefenceGameCamera.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
ATowerDefenceGameCamera::ATowerDefenceGameCamera()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Boom"));
	MainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	MarkBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Sign"));

	CameraBoom->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	MainCamera->AttachToComponent(CameraBoom, FAttachmentTransformRules::KeepRelativeTransform);
	MarkBox->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	CameraBoom->TargetArmLength = 800.f;
	//CameraBoom->RelativeRotation = FRotator(-60.f, 0.f, 0.f);
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));

	
	MarkBox->SetCollisionProfileName(TEXT("ControllerPawnProfile"));

}

// Called when the game starts or when spawned
void ATowerDefenceGameCamera::BeginPlay()
{
	Super::BeginPlay();
	
}



// Called to bind functionality to input
void ATowerDefenceGameCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATowerDefenceGameCamera::Zoom(bool bDirection, const float& ZoomSpeed)
{
	if (bDirection)
	{
		if (CameraBoom->TargetArmLength > 400)
		{
			CameraBoom->TargetArmLength -= ZoomSpeed * 2;
		}
	}
	else
	{
		if (CameraBoom->TargetArmLength < 800)
		{
			CameraBoom->TargetArmLength += ZoomSpeed * 2;
		}
	}
}

