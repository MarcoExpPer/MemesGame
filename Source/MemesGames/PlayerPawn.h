// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerPawn.generated.h"

class UFollowedByCameraComponent;

UCLASS()
class MEMESGAMES_API APlayerPawn : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerPawn();

	void MoveRight(float value);

	void DoJump();
	void DoStopJump();

	void Interact();

	UPROPERTY(EditDefaultsOnly)
	FVector RightDirection = FVector(1, 0, 0);

	UPROPERTY(EditDefaultsOnly)
	UFollowedByCameraComponent* FollowCameraComp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
