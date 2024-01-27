// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CakeProjectile.generated.h"

class UProjectileMovementComponent;
class UBoxComponent;

UCLASS()
class MEMESGAMES_API ACakeProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACakeProjectile();

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UProjectileMovementComponent* movementComp;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UBoxComponent* boxCol;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	float StunDuration = 1.f;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	float KnockbackStrength = 2500;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	float ScoreOnHit = 10.f;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	FVector KnockbackDirection = FVector(0, 1, 0);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnCakeOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
