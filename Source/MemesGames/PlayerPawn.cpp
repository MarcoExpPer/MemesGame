// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/FollowedByCameraComponent.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FollowCameraComp = CreateDefaultSubobject<UFollowedByCameraComponent>(TEXT("Follow Camera Comp"));
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
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Interact!"));
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

