// Copyright Epic Games, Inc. All Rights Reserved.


#include "MemesGamesGameModeBase.h"

void AMemesGamesGameModeBase::AddScore(float Amount, bool AddToPlayer1)
{
    AddToPlayer1 ? Player1Score += Amount : Player2Score += Amount;

    OnScoreUpdate.Broadcast(AddToPlayer1, AddToPlayer1 ? Player1Score : Player2Score);
    if (Player1Score >= ScoreToLose) {
        //Player 1 loses
        OnMatchEnd.Broadcast(EMatchEndReason::ME_PLAYER2_WINS);
    }
    else if(Player2Score >= ScoreToLose){
        //Player 2 loses
        OnMatchEnd.Broadcast(EMatchEndReason::ME_PLAYER1_WINS);
    }
}

void AMemesGamesGameModeBase::StartTimer()
{
    GetWorldTimerManager().SetTimer(CountDownHandle, this, &AMemesGamesGameModeBase::TimerTick, 1.f, true);
}

void AMemesGamesGameModeBase::BeginPlay()
{
    Super::BeginPlay();
}

void AMemesGamesGameModeBase::TimerTick()
{
    CurrentTimer -= 1;
    OnTimerUpdate.Broadcast(CurrentTimer);

    if (CurrentTimer <= 0) {
        OnMatchEnd.Broadcast(EMatchEndReason::ME_TIMEOUT);
    }
}
