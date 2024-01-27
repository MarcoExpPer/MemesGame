// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HammerSwing.generated.h"

class UBoxComponent;
class USceneComponent;

UCLASS()
class MEMESGAMES_API AHammerSwing : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHammerSwing();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USceneComponent* sceneComp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UBoxComponent* boxCol;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float StunDuration = 1.5f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float KnockbackStrength = 1300;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float ScoreOnHit = 30.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector KnockbackDirection = FVector(0, 1, 0.3);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float InitialPitch = 0.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float FinalPitch = -95.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float RotationSpeed = 7.5f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnHammerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	bool CanDoHit = true;
};
