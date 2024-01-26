// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerDuoController.h"
#include "PlayerPawn.h"

void APlayerDuoController::SpawnPlayerPawn(FTransform SpawnTransform, bool isPlayer1)
{
	APlayerPawn* NewPlayerPawn = GetWorld()->SpawnActor<APlayerPawn>(PlayerClass.LoadSynchronous(), SpawnTransform, FActorSpawnParameters());
	if (isPlayer1) {
		Pawn1 = NewPlayerPawn;
	}
	else {
		Pawn2 = NewPlayerPawn;
	}
}

void APlayerDuoController::MoveRightP1(float value)
{
	Pawn1->MoveRight(value);
}

void APlayerDuoController::MoveRightP2(float value)
{
	Pawn2->MoveRight(value);
}

void APlayerDuoController::JumpP1()
{
	Pawn1->DoJump();
}

void APlayerDuoController::JumpP2()
{
	Pawn2->DoJump();
}

void APlayerDuoController::StopJumpP1()
{
	Pawn1->DoStopJump();
}

void APlayerDuoController::StopJumpP2()
{
	Pawn2->DoStopJump();
}

void APlayerDuoController::InteractP1()
{
	Pawn1->Interact();
}

void APlayerDuoController::InteractP2()
{
	Pawn2->Interact();
}
