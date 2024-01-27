// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractComponent.h"
#include <Kismet/KismetSystemLibrary.h>
#include "InteractableComponent.h"

// Sets default values for this component's properties
UInteractComponent::UInteractComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

bool UInteractComponent::Interact()
{
	FVector SphereCentre = GetOwner()->GetActorLocation() + GetOwner()->GetActorForwardVector() * InteractRange;

	DrawDebugSphere(GetWorld(), SphereCentre, InteractRadius, 32, FColor::Red);

	TArray<AActor*> toIgnore;
	toIgnore.Push(GetOwner());

	TArray<FHitResult> OutHit;
	UKismetSystemLibrary::SphereTraceMultiByProfile(GetWorld(), SphereCentre, SphereCentre,
		InteractRadius, "Pawn", false, toIgnore, EDrawDebugTrace::None, OutHit, true);

	UInteractableComponent* ClosestInteractable = nullptr;
	float ClosestDistance = TNumericLimits<float>::Max();

	for (FHitResult hit : OutHit) {
		if(IsValid(hit.GetActor())){
			UInteractableComponent* InteractableHit = Cast<UInteractableComponent>(hit.GetActor()->GetComponentByClass(UInteractableComponent::StaticClass()));

			if (InteractableHit != nullptr && InteractableHit->CanBeInteracted()) {

				FVector HitLocation = hit.GetActor()->GetActorLocation();
				float NewDistance = FVector::Dist2D(GetOwner()->GetActorLocation(), HitLocation);

				if (NewDistance < ClosestDistance) {

					ClosestDistance = NewDistance;
					ClosestInteractable = InteractableHit;

				}
			}
		}
		
	}

	if (ClosestInteractable != nullptr) {
		ClosestInteractable->Interact(GetOwner());
		return true;
	}
	return false;
}