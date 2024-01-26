// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerDuoController.generated.h"


class APlayerPawn;

UCLASS()
class MEMESGAMES_API APlayerDuoController : public APlayerController
{
	GENERATED_BODY()
	

public:
	UFUNCTION(BlueprintCallable)
	void SpawnPlayerPawn(FTransform SpawnTransform, bool isPlayer1);

	UFUNCTION(BlueprintCallable)
	void MoveRightP1(float value);
	UFUNCTION(BlueprintCallable)
	void MoveRightP2(float value);

	UFUNCTION(BlueprintCallable)
	void JumpP1();
	UFUNCTION(BlueprintCallable)
	void JumpP2();

	UFUNCTION(BlueprintCallable)
	void StopJumpP1();
	UFUNCTION(BlueprintCallable)
	void StopJumpP2();

	UFUNCTION(BlueprintCallable)
	void InteractP1();
	UFUNCTION(BlueprintCallable)
	void InteractP2();

	UFUNCTION(BlueprintCallable)
	APlayerPawn* GetPlayer1() { return Pawn1; }
	UFUNCTION(BlueprintCallable)
	APlayerPawn* GetPlayer2() { return Pawn2; }

	UPROPERTY(EditDefaultsOnly)
	TSoftClassPtr<APlayerPawn> PlayerClass;

private:
	APlayerPawn* Pawn1;
	APlayerPawn* Pawn2;

	

};
