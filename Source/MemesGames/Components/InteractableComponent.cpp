// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableComponent.h"

UInteractableComponent::UInteractableComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInteractableComponent::Interact(AActor* Interactor)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Interact! ") + GetOwner()->GetName());
}