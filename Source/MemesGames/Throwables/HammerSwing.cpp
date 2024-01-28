// Fill out your copyright notice in the Description page of Project Settings.


#include "HammerSwing.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include <MemesGames/Throwables/ThrowableItem.h>
#include <MemesGames/PlayerPawn.h>

AHammerSwing::AHammerSwing()
{
	PrimaryActorTick.bCanEverTick = true;

	sceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Comp"));
	SetRootComponent(sceneComp);

	boxCol = CreateDefaultSubobject<UBoxComponent>(TEXT("Colision"));
	boxCol->SetupAttachment(RootComponent);

}

void AHammerSwing::Tick(float DeltaTime)
{
	float NewPitch = FMath::Lerp(GetActorRotation().Pitch, FinalPitch, DeltaTime * RotationSpeed);
	SetActorRotation(FRotator(NewPitch, GetActorRotation().Yaw, GetActorRotation().Roll));

	if (FMath::IsNearlyEqual(NewPitch, FinalPitch, 5.f)) {
		Destroy();
	}
}

void AHammerSwing::BeginPlay()
{
	Super::BeginPlay();
	boxCol->OnComponentBeginOverlap.AddDynamic(this, &AHammerSwing::OnHammerOverlap);

	SetActorRotation(FRotator(InitialPitch, GetActorRotation().Yaw, GetActorRotation().Roll));

	FAttachmentTransformRules Rules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, false);
	AttachToComponent((Cast<APlayerPawn>(GetInstigator()))->ItemJointPoint, Rules);
}

void AHammerSwing::OnHammerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor->IsA(AThrowableItem::StaticClass())
		&& OtherActor != GetInstigator() 
		&& CanDoHit) {

		if (APlayerPawn* PlayerPawn = Cast<APlayerPawn>(OtherActor)) {
			CanDoHit = false;

			PlayerPawn->Stun(StunDuration);

			bool bInvertY = GetInstigator()->GetActorForwardVector().Y < 0;
			FVector FinalKnockback = FVector(0.f, KnockbackDirection.Y * bInvertY ? -1 : 1, KnockbackDirection.Z);
			PlayerPawn->KnockBack(FinalKnockback, KnockbackStrength);

			PlayerPawn->AddScore(ScoreOnHit);
		}
	}
}
