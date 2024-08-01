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
	Camera->bDrawFrustumAllowed = true;
	
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

void AInteligentCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (WatchList.Num() > 0) {
		AActor* LeftMostCharacter = WatchList[0];
		AActor* RightMostCharacter = WatchList[0];
		AActor* UpMostCharacter = WatchList[0];
		AActor* DownMostCharacter = WatchList[0];

		for (AActor* actor : WatchList) {
			if (actor->GetActorLocation().Y < LeftMostCharacter->GetActorLocation().Y) {
				LeftMostCharacter = actor;
			}

			if (actor->GetActorLocation().Y > RightMostCharacter->GetActorLocation().Y) {
				RightMostCharacter = actor;
			}
			
			if (actor->GetActorLocation().Z > UpMostCharacter->GetActorLocation().Z) {
				UpMostCharacter = actor;
			}

			if (actor->GetActorLocation().Z < DownMostCharacter->GetActorLocation().Z)
			{
				DownMostCharacter = actor;
			}
		}
		
		float LeftMostY = LeftMostCharacter->GetActorLocation().Y - ExtraHOffset;
		float RightMostY = RightMostCharacter->GetActorLocation().Y + ExtraHOffset;
		float TopMostZ = UpMostCharacter->GetActorLocation().Z + ExtraVOFfset;
		float BottomMostZ = DownMostCharacter->GetActorLocation().Z - ExtraVOFfset;

		if(false){
			FVector LeftTopPoint = FVector(0, LeftMostY, TopMostZ);
			FVector RightTopPoint = FVector(0, RightMostY, TopMostZ);

			FVector LeftBottomPoint = FVector(0, LeftMostY, BottomMostZ);
			FVector RightBottomPoint = FVector(0, RightMostY, BottomMostZ);
			
			DrawDebugSphere(GetWorld(), LeftMostCharacter->GetActorLocation(), 50.f, 32, FColor::Green);
			DrawDebugSphere(GetWorld(), RightMostCharacter->GetActorLocation(), 50.f, 32, FColor::Red);
			DrawDebugSphere(GetWorld(), UpMostCharacter->GetActorLocation(), 50.f, 32, FColor::Blue);
			DrawDebugSphere(GetWorld(), DownMostCharacter->GetActorLocation(), 50.f, 32, FColor::Orange);
				
			DrawDebugLine(GetWorld(), LeftTopPoint, RightTopPoint, FColor::Red);
			DrawDebugLine(GetWorld(), LeftTopPoint, LeftBottomPoint, FColor::Red);

			DrawDebugLine(GetWorld(), RightBottomPoint, RightTopPoint, FColor::Red);
			DrawDebugLine(GetWorld(), RightBottomPoint, LeftBottomPoint, FColor::Red);
		}
		
		float HorizontalWidth = RightMostY - LeftMostY;
		float OrthoWidthAlpha = (HorizontalWidth - minZoomDistance) / maxZoomDistance;
		float newOrthoWidth = FMath::Lerp(minZoomDistance, maxZoomDistance, OrthoWidthAlpha);
		Camera->OrthoWidth = FMath::Lerp(Camera->OrthoWidth, newOrthoWidth, DeltaTime * CameraAdjustSpeed);

		float HorizontalLocation = LeftMostY + HorizontalWidth/2;
		
		float VerticalWidth = TopMostZ - BottomMostZ;
		float VerticalLocation = BottomMostZ + VerticalWidth/2;
		
		FVector TargetCameraLocation = FVector(GetActorLocation().X, HorizontalLocation,  VerticalLocation);
		SetActorLocation(FMath::Lerp(GetActorLocation(), TargetCameraLocation, DeltaTime * CameraAdjustSpeed));
	}
}
