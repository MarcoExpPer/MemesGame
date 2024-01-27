// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteligentCamera.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class MEMESGAMES_API AInteligentCamera : public AActor
{
	GENERATED_BODY()

public:
	AInteligentCamera();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UCameraComponent* Camera;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USpringArmComponent* Arm;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CameraAdjustSpeed = 3.f;

	void AddActorToWatchlist(AActor* actor);
	void RemoveActorFromWatchlist(AActor* actor);

protected:
	virtual void Tick(float DeltaTime) override;

private:
	TArray<AActor*> WatchList;
	
};
