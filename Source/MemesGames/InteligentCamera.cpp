// Fill out your copyright notice in the Description page of Project Settings.


#include "InteligentCamera.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

AInteligentCamera::AInteligentCamera()
{
	PrimaryActorTick.bCanEverTick = true;

	Arm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Arm"));
	SetRootComponent(Arm);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);

	Camera->SetProjectionMode(ECameraProjectionMode::Orthographic);
}

void AInteligentCamera::AddActorToWatchlist(AActor* actor)
{
	WatchList.Push(actor);
}

void AInteligentCamera::RemoveActorFromWatchlist(AActor* actor)
{
	WatchList.Remove(actor);
}

float minZoomDistance = 3000;
float maxZoomDistance = 10000.f;

void AInteligentCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (WatchList.Num() > 0) {
		AActor* LeftMostCharacter = nullptr;
		AActor* RightMostCharacter = nullptr;
		AActor* UpMostCharacter = nullptr;
		AActor* DownMostCharacter = nullptr;

		for (AActor* actor : WatchList) {
			if (!IsValid(LeftMostCharacter)) {
				LeftMostCharacter = actor;
			}
			else {
				if (actor->GetActorLocation().Y < LeftMostCharacter->GetActorLocation().Y) {
					LeftMostCharacter = actor;
				}
			}

			if (!IsValid(RightMostCharacter)) {
				RightMostCharacter = actor;
			}
			else {
				if (actor->GetActorLocation().Y > RightMostCharacter->GetActorLocation().Y) {
					RightMostCharacter = actor;
				}
			}

			if (!IsValid(UpMostCharacter)) {
				UpMostCharacter = actor;
			}
			else {
				if (actor->GetActorLocation().Z > UpMostCharacter->GetActorLocation().Z) {
					UpMostCharacter = actor;
				}
			}

			if (!IsValid(DownMostCharacter)) {
				DownMostCharacter = actor;
			}
			else {
				if (actor->GetActorLocation().Z < DownMostCharacter->GetActorLocation().Z) {
					DownMostCharacter = actor;
				}
			}
		}

		float HDistance = RightMostCharacter->GetActorLocation().Y - LeftMostCharacter->GetActorLocation().Y;
		float YLocation = LeftMostCharacter->GetActorLocation().Y + (HDistance)/2;
		float ZLocation = DownMostCharacter->GetActorLocation().Z + (UpMostCharacter->GetActorLocation().Z - DownMostCharacter->GetActorLocation().Z)/4;

		float newOrthoWidth = FMath::Lerp(minZoomDistance, maxZoomDistance, (HDistance - minZoomDistance) / maxZoomDistance);
		Camera->OrthoWidth = FMath::Lerp(Camera->OrthoWidth, newOrthoWidth, DeltaTime * CameraAdjustSpeed);
		SetActorLocation(FMath::Lerp(GetActorLocation(), FVector(0, YLocation, ZLocation), DeltaTime * CameraAdjustSpeed));
	}
}
