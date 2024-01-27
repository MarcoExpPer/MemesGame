// Fill out your copyright notice in the Description page of Project Settings.


#include "BoxTrickProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/BoxComponent.h"
#include <MemesGames/PlayerPawn.h>
#include "GameFramework/CharacterMovementComponent.h"
#include <MemesGames/Throwables/ThrowableItem.h>
#include "Components/SphereComponent.H"
// Sets default values
ABoxTrickProjectile::ABoxTrickProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	boxCol = CreateDefaultSubobject<UBoxComponent>(TEXT("Colision"));
	SetRootComponent(boxCol);

	sphereCol = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Colision"));
	sphereCol->SetupAttachment(RootComponent);

	movementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Move Comp"));
}

// Called when the game starts or when spawned
void ABoxTrickProjectile::BeginPlay()
{
	Super::BeginPlay();
	boxCol->OnComponentBeginOverlap.AddDynamic(this, &ABoxTrickProjectile::OnBoxTrickOverlap);
	sphereCol->OnComponentBeginOverlap.AddDynamic(this, &ABoxTrickProjectile::OnSphereTrickOverlap);
}

void ABoxTrickProjectile::OnBoxTrickOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	switch (TrickState) {
	case EBoxTrickState::TS_FLYING: {
		//Dont collide with owner or throwable
		if (OtherActor->IsA(AThrowableItem::StaticClass()) || OtherActor == GetInstigator()) return;

		//Collide only with WorldDynamic and WorldStatic
		if (OtherComp->GetCollisionObjectType() == ECollisionChannel::ECC_WorldDynamic
			|| OtherComp->GetCollisionObjectType() == ECollisionChannel::ECC_WorldStatic) {

			TrickState = EBoxTrickState::TS_DROPPING;
			movementComp->StopMovementImmediately();

			FCollisionObjectQueryParams queryPrms;
			queryPrms.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldDynamic);
			queryPrms.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldStatic);

			FCollisionQueryParams ColParams;
			ColParams.AddIgnoredActor(this);
			ColParams.AddIgnoredActor(GetInstigator());

			FHitResult out;
			FVector StartLocation = boxCol->GetScaledBoxExtent();
			StartLocation = FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z - StartLocation.Z + 1);
			FVector EndLocation = StartLocation + FVector::DownVector * 15;

			DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, true);

			if (GetWorld()->LineTraceSingleByObjectType(out, StartLocation, EndLocation, queryPrms, ColParams)) {
				TrickState = EBoxTrickState::TS_CHARGING;
				ToRecharging();
				movementComp->ProjectileGravityScale = 0;

				DrawDebugPoint(GetWorld(), out.ImpactPoint, 20, FColor::Blue, true);
			}
		}
		break;
	}
	case EBoxTrickState::TS_DROPPING: {
		if (OtherActor->IsA(AThrowableItem::StaticClass()) || OtherActor == GetInstigator()) return;

		//Collide only with WorldDynamic and WorldStatic
		if (OtherComp->GetCollisionObjectType() == ECollisionChannel::ECC_WorldDynamic
			|| OtherComp->GetCollisionObjectType() == ECollisionChannel::ECC_WorldStatic) {

			TrickState = EBoxTrickState::TS_CHARGING;
			ToRecharging();

			movementComp->StopMovementImmediately();
			movementComp->ProjectileGravityScale = 0;
			movementComp->Deactivate();
		}
		break;
	}
	}
}

void ABoxTrickProjectile::OnSphereTrickOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (TrickState != EBoxTrickState::TS_READY) return;
	if (HasHit) return;

	TryKnockback(OtherActor);
}

void ABoxTrickProjectile::ToRecharging()
{
	GetWorldTimerManager().SetTimer(RechargeHandle, this, &ABoxTrickProjectile::ToReady, TimeToRecharge, false);
	OnRechargeStarts.Broadcast();
}

void ABoxTrickProjectile::ToReady()
{
	TrickState = EBoxTrickState::TS_READY;
	OnReadyStarts.Broadcast();

	TArray<AActor*> Actors;
	sphereCol->GetOverlappingActors(Actors);

	for (AActor* actor : Actors) {
		if (HasHit) break;
		
		TryKnockback(actor);
	}
}

void ABoxTrickProjectile::TryKnockback(AActor* actor)
{
	if (APlayerPawn* PlayerPawn = Cast<APlayerPawn>(actor)) {
		HasHit = true;
		PlayerPawn->Stun(StunDuration);

		PlayerPawn->GetCharacterMovement()->AddRadialImpulse(GetActorLocation(), KonckbackRadius, KnockbackStrength, ERadialImpulseFalloff(), true);

		PlayerPawn->AddScore(ScoreOnHit);

		OnBoxActivated.Broadcast();
	}
}
