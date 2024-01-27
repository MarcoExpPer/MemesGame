// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerPawn.generated.h"

class UFollowedByCameraComponent;
class UInteractComponent;
class AThrowableItem;
class AMemesGamesGameModeBase;

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

	void Throw();

	void KnockBack(FVector Direction, float Strength);
	void Stun(float duration);

	virtual void Tick(float DeltaTime) override;

	void SetThrowableEquiped(AThrowableItem* NewThrowable) { ThrowableEquiped = NewThrowable; }

	UPROPERTY(EditDefaultsOnly)
	FVector RightDirection = FVector(1, 0, 0);

	UPROPERTY(EditDefaultsOnly)
	UFollowedByCameraComponent* FollowCameraComp;

	UPROPERTY(EditDefaultsOnly)
	UInteractComponent* InteractComp;

	void SetIsStunned(bool newState) { bIsStunned = newState; }

	UFUNCTION(BlueprintCallable)
	bool IsStunned() {return bIsStunned;}

	void SetIsPlayer1(bool NewIsPlayer1) { bIsPlayer1 = NewIsPlayer1; }

	void AddScore(float Amount);
protected:
	virtual void BeginPlay() override;

private:
	bool bIsStunned = false;
	FTimerHandle StunHandle;
	AThrowableItem* ThrowableEquiped;
	bool bIsPlayer1 = false;
	AMemesGamesGameModeBase* gm;
};
