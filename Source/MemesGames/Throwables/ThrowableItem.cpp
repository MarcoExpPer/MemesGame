// Fill out your copyright notice in the Description page of Project Settings.


#include "ThrowableItem.h"
#include <MemesGames/PlayerPawn.h>
#include <MemesGames/Components/InteractableComponent.h>
#include <MemesGames/Components/FollowedByCameraComponent.h>
#include "Engine/EngineTypes.h"

AThrowableItem::AThrowableItem()
{
	PrimaryActorTick.bCanEverTick = false;

	FollowCameraComp = CreateDefaultSubobject<UFollowedByCameraComponent>(TEXT("Follow Camera Comp"));
	InteractableComp = CreateDefaultSubobject<UInteractableComponent>(TEXT("Interact Component"));
}

void AThrowableItem::Throw(APawn* actor)
{
	FVector SpawnLocation = GetActorLocation();
	FRotator SpawnRotation = actor->GetActorRotation();
	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = actor;

	GetWorld()->SpawnActor<AActor>(ItemToSpawnClass, SpawnLocation, SpawnRotation, SpawnParams);

	Destroy();
}

void AThrowableItem::Interacted(AActor* actor)
{
	OnPickedFromFloor.ExecuteIfBound();

	FAttachmentTransformRules Rules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, false);
	AttachToActor(actor, Rules);

	Cast<APlayerPawn>(actor)->SetThrowableEquiped(this);
}

void AThrowableItem::BeginPlay()
{
	Super::BeginPlay();

	InteractableComp->GetOnInteract()->BindUObject(this, &AThrowableItem::Interacted);
	
}
