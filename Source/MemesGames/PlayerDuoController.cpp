// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerDuoController.h"
#include "PlayerPawn.h"
#include "InteligentCamera.h"
#include <Kismet/GameplayStatics.h>
#include <MemesGames/PlayersData.h>

void APlayerDuoController::SpawnPlayerPawn(FTransform SpawnTransform, bool isPlayer1)
{
	EPlayerSkin SkinEnum = isPlayer1 ? PlayersData->Player1Skin : PlayersData->Player2Skin;
	UClass* SkinClass = SkinEnum == EPlayerSkin::PS_BOY_1 ? PlayerBoy1Class.LoadSynchronous() : SkinEnum == EPlayerSkin::PS_GIRL_1 ? 
		PlayerGirl1Class.LoadSynchronous() : SkinEnum == EPlayerSkin::PS_BOY_2 ? PlayerBoy2Class.LoadSynchronous() : PlayerGirl2Class.LoadSynchronous();
	FActorSpawnParameters spawnParams;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	APlayerPawn* NewPlayerPawn = GetWorld()->SpawnActor<APlayerPawn>(SkinClass, SpawnTransform, spawnParams);
	NewPlayerPawn->SetIsPlayer1(isPlayer1);

	isPlayer1 ? Pawn1 = NewPlayerPawn : Pawn2 = NewPlayerPawn;
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

void APlayerDuoController::BeginPlay()
{
	PlayersData = Cast<UPlayersData>(UGameplayStatics::GetGameInstance(GetWorld()));

	Super::BeginPlay();
}
