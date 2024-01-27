// Fill out your copyright notice in the Description page of Project Settings.


#include "WaterFlower.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include <MemesGames/Throwables/ThrowableItem.h>
#include <MemesGames/PlayerPawn.h>

// Sets default values
AWaterFlower::AWaterFlower()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	sceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root Comp"));
	SetRootComponent(sceneComp);

	boxCol = CreateDefaultSubobject<UBoxComponent>(TEXT("Colision"));
	boxCol->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AWaterFlower::BeginPlay()
{
	Super::BeginPlay();
	boxCol->OnComponentBeginOverlap.AddDynamic(this, &AWaterFlower::OnWaterOverlap);

	FAttachmentTransformRules Rules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, false);
	AttachToActor(GetInstigator(), Rules);

	TArray<AActor*> output;
	boxCol->GetOverlappingActors(output);

	for (AActor* actor : output) {
		if (!actor->IsA(AThrowableItem::StaticClass())
			&& actor != GetInstigator()) {

			if (APlayerPawn* PlayerPawn = Cast<APlayerPawn>(actor)) {
				PlayerPawn->Poison(DebuffDuration);
				PlayerPawn->AddScore(ScoreOnHit);
			}
		}
	}

	FTimerHandle uselessHandle;
	GetWorldTimerManager().SetTimer(uselessHandle, [this] {
		Destroy();
		}, WaterDuration, false);
}

void AWaterFlower::OnWaterOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor->IsA(AThrowableItem::StaticClass())
		&& OtherActor != GetInstigator()) {

		if (APlayerPawn* PlayerPawn = Cast<APlayerPawn>(OtherActor)) {
			PlayerPawn->Poison(DebuffDuration);
			PlayerPawn->AddScore(ScoreOnHit);
		}
	}
}

