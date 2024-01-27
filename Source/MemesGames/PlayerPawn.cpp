// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/FollowedByCameraComponent.h"
#include "Components/InteractComponent.h"
#include "Throwables/ThrowableItem.h"
#include "MemesGames/MemesGamesGameModeBase.h"
#include <Kismet/GameplayStatics.h>
//#include "PaperFlipbookComponent.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	FollowCameraComp = CreateDefaultSubobject<UFollowedByCameraComponent>(TEXT("Follow Camera Comp"));
	InteractComp = CreateDefaultSubobject<UInteractComponent>(TEXT("Interact Component"));
}

void APlayerPawn::MoveRight(float value)
{
	if (bIsStunned) return;
	if (AreControlsInverted) value *= -1;

	AddMovementInput(RightDirection, value);
	GetCharacterMovement()->AddInputVector(RightDirection * value);
}

void APlayerPawn::DoJump()
{
	if (bIsStunned) return;
	Jump();
}

void APlayerPawn::DoStopJump()
{
	StopJumping();
}

void APlayerPawn::Interact()
{
	if (ThrowableEquiped == nullptr) {
		if (InteractComp->Interact()) {
			OnDoAnimation.Broadcast(EPlayerAnims::PA_PICKUP);
		}
	}
	else {
		Throw();
	}
}

void APlayerPawn::Throw()
{
	OnDoAnimation.Broadcast(EPlayerAnims::PA_THROW);

	FTimerHandle uselessHandle;
	GetWorld()->GetTimerManager().SetTimer(uselessHandle, [this] {
		ThrowableEquiped->Throw(this);
		ThrowableEquiped = nullptr;
	}, 0.20f, false);

	//ThrowableEquiped->Throw(this);
	//ThrowableEquiped = nullptr;
}

void APlayerPawn::KnockBack(FVector Direction, float Strength)
{
	GetCharacterMovement()->AddImpulse(Direction * Strength + FVector::UpVector * 10, true);
}

void APlayerPawn::Stun(float duration)
{
	bIsStunned = true;
	
	FTimerDelegate TimerDel;
	TimerDel.BindUObject(this, &APlayerPawn::SetIsStunned, false);

	GetWorldTimerManager().SetTimer(StunHandle, TimerDel, duration, false);
}

void APlayerPawn::Poison(float duration)
{
	GetWorldTimerManager().ClearTimer(PoisonHandle);
	AreControlsInverted = true;

	GetWorldTimerManager().SetTimer(PoisonHandle, [this] {
		AreControlsInverted = false;
		}, duration, false);
}

bool APlayerPawn::IsStunned()
{
	return bIsStunned;
}


void APlayerPawn::AddScore(float Amount)
{
	gm->AddScore(Amount, bIsPlayer1);
}

void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	gm = Cast<AMemesGamesGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
}

void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

