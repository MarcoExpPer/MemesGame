// Fill out your copyright notice in the Description page of Project Settings.


#include "BananaProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/BoxComponent.h"
#include <MemesGames/PlayerPawn.h>
#include <MemesGames/Throwables/ThrowableItem.h>

// Sets default values
ABananaProjectile::ABananaProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	boxCol = CreateDefaultSubobject<UBoxComponent>(TEXT("Colision"));
	SetRootComponent(boxCol);

	movementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Move Comp"));
}

// Called when the game starts or when spawned
void ABananaProjectile::BeginPlay()
{
	Super::BeginPlay();
	boxCol->OnComponentBeginOverlap.AddDynamic(this, &ABananaProjectile::OnBananaOverlap);

	SetActorRotation(FRotator(InitialPitch, GetActorRotation().Yaw, GetActorRotation().Roll));

	movementComp->Velocity = GetActorForwardVector() * movementComp->InitialSpeed;

}

void ABananaProjectile::OnBananaOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	switch (BananaState) {
	case EBananaState::BS_FLYING: {
		//Dont collide with owner or throwable
		if (OtherActor->IsA(AThrowableItem::StaticClass()) || OtherActor == GetInstigator()) return;

		//Collide only with WorldDynamic and WorldStatic
		if (OtherComp->GetCollisionObjectType() == ECollisionChannel::ECC_WorldDynamic
			|| OtherComp->GetCollisionObjectType() == ECollisionChannel::ECC_WorldStatic) { 

			BananaState = EBananaState::BS_DROPPING;
			movementComp->StopMovementImmediately();

			FCollisionObjectQueryParams queryPrms;
			queryPrms.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldDynamic);
			queryPrms.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldStatic);

			FCollisionQueryParams ColParams;
			ColParams.AddIgnoredActor(this);
			ColParams.AddIgnoredActor(GetInstigator());

			FHitResult out;
			FVector StartLocation = boxCol->GetScaledBoxExtent();
			StartLocation = FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z - StartLocation.Z + 2);
			FVector EndLocation = StartLocation + FVector::DownVector * 10;

			if (GetWorld()->LineTraceSingleByObjectType(out, StartLocation, EndLocation, queryPrms, ColParams)) {
				BananaState = EBananaState::BS_ONFLOOR;
				movementComp->ProjectileGravityScale = 0;

				DrawDebugPoint(GetWorld(), out.ImpactPoint, 20, FColor::Blue, true);
			}
		}
		break;
	}
	case EBananaState::BS_DROPPING: {
		if (OtherActor->IsA(AThrowableItem::StaticClass()) || OtherActor == GetInstigator()) return;

		//Collide only with WorldDynamic and WorldStatic
		if (OtherComp->GetCollisionObjectType() == ECollisionChannel::ECC_WorldDynamic
			|| OtherComp->GetCollisionObjectType() == ECollisionChannel::ECC_WorldStatic) {

			BananaState = EBananaState::BS_ONFLOOR;
			movementComp->StopMovementImmediately();
			movementComp->ProjectileGravityScale = 0;
			movementComp->Deactivate();
		}
			break;
	}
	case EBananaState::BS_ONFLOOR: {

		if (APlayerPawn* PlayerPawn = Cast<APlayerPawn>(OtherActor)) {
			PlayerPawn->Stun(StunDuration);

			bool bInvertY = GetVelocity().Y < 0;
			FVector FinalKnockback = FVector(0.f, KnockbackDirection.Y * bInvertY ? -1 : 1, KnockbackDirection.Z);
			PlayerPawn->KnockBack(FinalKnockback, KnockbackStrength);

			PlayerPawn->AddScore(ScoreOnHit);

			Destroy();
		}

		break;
	}
	}
}
