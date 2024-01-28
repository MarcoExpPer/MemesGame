// Copyright Epic Games, Inc. All Rights Reserved.


#include "MemesGamesGameModeBase.h"
#include "PlayersData.h"
#include "Kismet/GameplayStatics.h"

void AMemesGamesGameModeBase::AddScore(float Amount, bool AddToPlayer1)
{
    if (AddToPlayer1) {
        Player1Score += Amount;
        gInstance->Player1Score = Player1Score;

        OnScoreUpdate.Broadcast(true, Player1Score);

        if (Player1Score >= ScoreToLose) {
            //Player 1 loses
            OnMatchEnd.Broadcast(EMatchEndReason::ME_PLAYER2_WINS);
            UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), EndScreenWorld);
        }
    }
    else {
        Player2Score += Amount;
        gInstance->Player2Score = Player2Score;

        OnScoreUpdate.Broadcast(false, Player2Score);

        if (Player2Score >= ScoreToLose) {
            //Player 2 loses
            OnMatchEnd.Broadcast(EMatchEndReason::ME_PLAYER1_WINS);
            UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), EndScreenWorld);
        }
    }
}

void AMemesGamesGameModeBase::StartTimer()
{
    OnTimerUpdate.Broadcast(MatchTime);
    CurrentTimer = MatchTime;
    GetWorldTimerManager().SetTimer(CountDownHandle, this, &AMemesGamesGameModeBase::TimerTick, 1.f, true);
}

void AMemesGamesGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    gInstance = Cast<UPlayersData>(UGameplayStatics::GetGameInstance(GetWorld()));
}

void AMemesGamesGameModeBase::TimerTick()
{
    CurrentTimer -= 1;
    OnTimerUpdate.Broadcast(CurrentTimer);

    if (CurrentTimer < 0) {
        OnMatchEnd.Broadcast(EMatchEndReason::ME_TIMEOUT);
        UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), EndScreenWorld);
    }
}
