// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableComponent.h"
#include <MemesGames/PlayerPawn.h>

UInteractableComponent::UInteractableComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInteractableComponent::Interact(AActor* Interactor)
{
	bCanBeInteracted = false;
	OnInteract.ExecuteIfBound(Cast<APlayerPawn>(Interactor));
}