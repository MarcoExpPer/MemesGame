// Fill out your copyright notice in the Description page of Project Settings.


#include "CakeProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/BoxComponent.h"
#include <MemesGames/PlayerPawn.h>
#include <MemesGames/Throwables/ThrowableItem.h>

// Sets default values
ACakeProjectile::ACakeProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	boxCol = CreateDefaultSubobject<UBoxComponent>(TEXT("Colision"));
	SetRootComponent(boxCol);

	movementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Move Comp"));
}

// Called when the game starts or when spawned
void ACakeProjectile::BeginPlay()
{
	Super::BeginPlay();
	boxCol->OnComponentBeginOverlap.AddDynamic(this, &ACakeProjectile::OnCakeOverlap);
}

void ACakeProjectile::OnCakeOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor->IsA(AThrowableItem::StaticClass()) 
		&& OtherActor != GetInstigator()) {

		if (APlayerPawn* PlayerPawn = Cast<APlayerPawn>(OtherActor)) {
			PlayerPawn->Stun(StunDuration);

			bool bInvertY = GetVelocity().Y < 0;
			FVector FinalKnockback = FVector(0.f, KnockbackDirection.Y * bInvertY ? -1 : 1, KnockbackDirection.Z);
			PlayerPawn->KnockBack(FinalKnockback, KnockbackStrength);

			PlayerPawn->AddScore(ScoreOnHit);
		}

		Destroy();
	}
}
