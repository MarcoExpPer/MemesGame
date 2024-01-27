// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractComponent.h"
#include <Kismet/KismetSystemLibrary.h>
#include "InteractableComponent.h"

// Sets default values for this component's properties
UInteractComponent::UInteractComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInteractComponent::Interact()
{
	FVector SphereCentre = GetOwner()->GetActorLocation() + GetOwner()->GetActorForwardVector() * InteractRange;

	DrawDebugSphere(GetWorld(), SphereCentre, InteractRadius, 32, FColor::Red);


	TArray<FHitResult> OutHit;
	UKismetSystemLibrary::SphereTraceMultiByProfile(GetWorld(), SphereCentre, SphereCentre,
		InteractRadius, "Pawn", false, TArray<AActor*>(), EDrawDebugTrace::None, OutHit, true);

	UInteractableComponent* Interactable = nullptr;
	float ClosestDistance = TNumericLimits<float>::Max();

	for (FHitResult hit : OutHit) {
		if (hit.bBlockingHit) {
			
			UInteractableComponent* InteractbleHit = Cast< UInteractableComponent>(hit.GetActor()->GetComponentByClass(UInteractableComponent::StaticClass()));

			if (InteractbleHit != nullptr) {

				FVector HitLocation = hit.GetActor()->GetActorLocation();
				float NewDistance = FVector::Dist2D(GetOwner()->GetActorLocation(), HitLocation);

				if (NewDistance < ClosestDistance) {

					ClosestDistance = NewDistance;
					Interactable = InteractbleHit;

				}
			}
		}
	}

	if (Interactable != nullptr) {
		Interactable->Interact(GetOwner());
	}
}