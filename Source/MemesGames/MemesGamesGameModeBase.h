// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MemesGamesGameModeBase.generated.h"

class UPlayersData;

UENUM(BlueprintType)
enum class EMatchEndReason : uint8 {
	ME_TIMEOUT,
	ME_PLAYER1_WINS,
	ME_PLAYER2_WINS
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMatchEnd, EMatchEndReason, MatchEndReason);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTimerUpdate, float, secondsLeft);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnScoreUpdate, bool, isPlayer1, float, newPoints);

UCLASS()
class MEMESGAMES_API AMemesGamesGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	void AddScore(float Amount, bool AddToPlayer1);

	float GetPlayer1Score() { return Player1Score; }
	float GetPlayer2Score() { return Player2Score; }
	UFUNCTION(BlueprintCallable)
	void StartTimer();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float ScoreToLose = 100;

	UPROPERTY(BlueprintAssignable)
	FOnMatchEnd OnMatchEnd;

	UPROPERTY(BlueprintAssignable)
	FOnTimerUpdate OnTimerUpdate;

	UPROPERTY(BlueprintAssignable)
	FOnScoreUpdate OnScoreUpdate;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSoftObjectPtr<UWorld> EndScreenWorld;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MatchTime = 180;

	UPlayersData* gInstance;

protected:
	virtual void BeginPlay() override;

private:
	float Player1Score = 0;
	float Player2Score = 0;

	float CurrentTimer;
	FTimerHandle CountDownHandle;

	UFUNCTION()
	void TimerTick();
};
