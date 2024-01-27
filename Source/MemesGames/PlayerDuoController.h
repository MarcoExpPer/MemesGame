// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerDuoController.generated.h"


class APlayerPawn;
class UPlayersData;

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

	UFUNCTION(BlueprintCallable)
	void SetPlayer1(APlayerPawn* Player1){ Pawn1 = Player1;}
	UFUNCTION(BlueprintCallable)
	void SetPlayer2(APlayerPawn* Player2) { Pawn2 = Player2; }

	UPROPERTY(EditDefaultsOnly)
	TSoftClassPtr<APlayerPawn> PlayerBoyClass;
	UPROPERTY(EditDefaultsOnly)
	TSoftClassPtr<APlayerPawn> PlayerGirlClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:
	APlayerPawn* Pawn1;
	APlayerPawn* Pawn2;

	UPlayersData* PlayersData;

	

};
