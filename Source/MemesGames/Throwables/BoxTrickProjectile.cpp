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

	USceneComponent* newRoot = CreateDefaultSubobject<USceneComponent>(TEXT("NewRoot"));
	SetRootComponent(newRoot);
	
	boxCol = CreateDefaultSubobject<UBoxComponent>(TEXT("Colision"));
	boxCol->SetupAttachment(RootComponent);

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
	
	SetActorRotation(FRotator(InitialPitch, GetActorRotation().Yaw, GetActorRotation().Roll));

	movementComp->Velocity = GetActorForwardVector() * movementComp->InitialSpeed;
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

			FHitResult Rightout;
			FVector RightStartLocation = FVector(GetActorLocation().X,
				GetActorLocation().Y + boxCol->GetScaledBoxExtent().Y,
				GetActorLocation().Z - boxCol->GetScaledBoxExtent().Z + 10);
			FVector RightEndLocation = RightStartLocation + FVector::DownVector * 20;

			GetWorld()->LineTraceSingleByObjectType(Rightout, RightStartLocation, RightEndLocation, queryPrms, ColParams);

			FHitResult Leftout;
			FVector LeftStartLocation = FVector(GetActorLocation().X,
				GetActorLocation().Y - boxCol->GetScaledBoxExtent().Y,
				GetActorLocation().Z - boxCol->GetScaledBoxExtent().Z + 10);
			FVector LeftEndLocation = LeftStartLocation + FVector::DownVector * 20;

			GetWorld()->LineTraceSingleByObjectType(Leftout, LeftStartLocation, LeftEndLocation, queryPrms, ColParams);

			if (Leftout.bBlockingHit || Rightout.bBlockingHit) {
				TrickState = EBoxTrickState::TS_CHARGING;
				ToRecharging();
				movementComp->ProjectileGravityScale = 0;
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
