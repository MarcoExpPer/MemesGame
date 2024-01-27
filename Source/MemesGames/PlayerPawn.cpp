// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/FollowedByCameraComponent.h"
#include "Components/InteractComponent.h"
#include "Throwables/ThrowableItem.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	FollowCameraComp = CreateDefaultSubobject<UFollowedByCameraComponent>(TEXT("Follow Camera Comp"));
	InteractComp = CreateDefaultSubobject<UInteractComponent>(TEXT("Interact Component"));
}

void APlayerPawn::MoveRight(float value)
{
	GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Yellow, FString::Printf(TEXT("Value: %f"), value));
	AddMovementInput(RightDirection, value);
	GetCharacterMovement()->AddInputVector(RightDirection* value);
}

void APlayerPawn::DoJump()
{
	Jump();
}

void APlayerPawn::DoStopJump()
{
	StopJumping();
}

void APlayerPawn::Interact()
{
	if (ThrowableEquiped == nullptr) {
		InteractComp->Interact();
	}
	else {
		Throw();
	}
}

void APlayerPawn::Throw()
{
	ThrowableEquiped->Throw(this);
	ThrowableEquiped = nullptr;
}

void APlayerPawn::KnockBack(FVector Direction, float Strength)
{
}

void APlayerPawn::Stun(float duration)
{

}

void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

