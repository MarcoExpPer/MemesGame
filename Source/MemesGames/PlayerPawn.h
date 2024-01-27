// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerPawn.generated.h"

class UFollowedByCameraComponent;
class UInteractComponent;

UCLASS()
class MEMESGAMES_API APlayerPawn : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerPawn();

	void MoveRight(float value);

	void DoJump();
	void DoStopJump();

	void Interact();

	UPROPERTY(EditDefaultsOnly)
	FVector RightDirection = FVector(1, 0, 0);

	UPROPERTY(EditDefaultsOnly)
	UFollowedByCameraComponent* FollowCameraComp;

	UPROPERTY(EditDefaultsOnly)
	UInteractComponent* InteractComp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
