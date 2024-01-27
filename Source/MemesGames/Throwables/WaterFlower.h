// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WaterFlower.generated.h"


class USceneComponent;
class UBoxComponent;

UCLASS()
class MEMESGAMES_API AWaterFlower : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWaterFlower();

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	USceneComponent* sceneComp;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UBoxComponent* boxCol;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	float DebuffDuration = 5.f;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	float ScoreOnHit = 5.f;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	float WaterDuration = 0.25f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnWaterOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
};