// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Curves/CurveFloat.h"
#include "Components/TimelineComponent.h"
#include "DrawText.generated.h"


UCLASS()
class SIMPLEDRAWTEXT_API ADrawText : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BaseAttribute", meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* Widget;

	UPROPERTY(EditDefaultsOnly, Category = "DrawText")
	float Height;

	UPROPERTY(EditDefaultsOnly, Category = "TimeLine")
	FRuntimeFloatCurve CurveFloatClass;

protected:
	FTimeline TimeLine;
	
public:	


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this actor's properties
	ADrawText();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void TimeLineRangeTime(float Value);

	UFUNCTION()
	void TimeLineFinished();

	void SetTextBlock(const FString& Intext, const FLinearColor& Color, float Percentage);

};
