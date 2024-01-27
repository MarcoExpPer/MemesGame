// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BananaProjectile.generated.h"

class UProjectileMovementComponent;
class UBoxComponent;

UENUM(BlueprintType)
enum class EBananaState : uint8 {
	BS_FLYING,
	BS_DROPPING,
	BS_ONFLOOR
};

UCLASS()
class MEMESGAMES_API ABananaProjectile : public AActor
{
	GENERATED_BODY()
	
public:

	ABananaProjectile();
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UProjectileMovementComponent* movementComp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UBoxComponent* boxCol;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float StunDuration = 1.5f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float KnockbackStrength = 500;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float ScoreOnHit = 15.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector KnockbackDirection = FVector(0, 1, 0.1);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EBananaState BananaState = EBananaState::BS_FLYING;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float InitialPitch = 55;

protected:

	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnBananaOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
};