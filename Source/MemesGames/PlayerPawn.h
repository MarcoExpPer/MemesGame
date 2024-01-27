// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
//#include "Paper2D/PaperSpriteComponent.h"
#include "PlayerPawn.generated.h"

class UFollowedByCameraComponent;
class UInteractComponent;
class AThrowableItem;
class AMemesGamesGameModeBase;

UENUM(BlueprintType)
enum class EPlayerAnims : uint8 {
	PA_IDLE,
	PA_WALK,
	PA_THROW,
	PA_PICKUP,
	PA_FALLDOWN,
	PA_JUMP
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerDoAnimation, EPlayerAnims, PlayerAnim);

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

	UFUNCTION(BlueprintCallable)
	void KnockBack(FVector Direction, float Strength);
	UFUNCTION(BlueprintCallable)
	void Stun(float duration);

	void Poison(float duration);

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
	bool IsStunned();

	void SetIsPlayer1(bool NewIsPlayer1) { bIsPlayer1 = NewIsPlayer1; }

	void AddScore(float Amount);

	UPROPERTY(BlueprintAssignable)
	FOnPlayerDoAnimation OnDoAnimation;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	bool bIsStunned = false;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	bool AreControlsInverted = false;
protected:
	virtual void BeginPlay() override;

private:

	FTimerHandle StunHandle;
	AThrowableItem* ThrowableEquiped;
	bool bIsPlayer1 = false;
	AMemesGamesGameModeBase* gm;

	FTimerHandle PoisonHandle;
};
