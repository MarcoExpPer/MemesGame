// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoxTrickProjectile.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRechargeStarts);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnReadyStarts);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBoxActivated);

class UProjectileMovementComponent;
class UBoxComponent;
class USphereComponent;

UENUM(BlueprintType)
enum class EBoxTrickState : uint8 {
	TS_FLYING,
	TS_DROPPING,
	TS_CHARGING,
	TS_READY
};

UCLASS()
class MEMESGAMES_API ABoxTrickProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoxTrickProjectile();

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UProjectileMovementComponent* movementComp;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UBoxComponent* boxCol;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	USphereComponent* sphereCol;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	float StunDuration = 2.f;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	float KnockbackStrength = 750;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	float ScoreOnHit = 25.f;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	float KonckbackRadius = 250;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	EBoxTrickState TrickState = EBoxTrickState::TS_FLYING;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	float InitialPitch = 35;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	float TimeToRecharge = 3;

	UPROPERTY(BlueprintAssignable)
	FOnRechargeStarts OnRechargeStarts;
	UPROPERTY(BlueprintAssignable)
	FOnReadyStarts OnReadyStarts;
	UPROPERTY(BlueprintAssignable)
	FOnBoxActivated OnBoxActivated;
protected:

	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnBoxTrickOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnSphereTrickOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void ToRecharging();
	void ToReady();
	void TryKnockback(AActor* actor);

	FTimerHandle RechargeHandle;

	bool HasHit = false;
};