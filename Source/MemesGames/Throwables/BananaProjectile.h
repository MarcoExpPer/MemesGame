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
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UProjectileMovementComponent* movementComp;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UBoxComponent* boxCol;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	float StunDuration = 1.5f;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	float KnockbackStrength = 500;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	float ScoreOnHit = 15.f;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	FVector KnockbackDirection = FVector(0, 1, 0.1);

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	EBananaState BananaState = EBananaState::BS_FLYING;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	float InitialPitch = 55;

protected:

	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnBananaOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
};