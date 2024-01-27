// Fill out your copyright notice in the Description page of Project Settings.


#include "FollowedByCameraComponent.h"
#include <MemesGames/InteligentCamera.h>
#include <Kismet/GameplayStatics.h>

// Sets default values for this component's properties
UFollowedByCameraComponent::UFollowedByCameraComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UFollowedByCameraComponent::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	if (bHasBeenAdded) {
		Camera->RemoveActorFromWatchlist(GetOwner());
	}
	
	Super::OnComponentDestroyed(bDestroyingHierarchy);
}

void UFollowedByCameraComponent::BeginPlay()
{
	Super::BeginPlay();
	
	Camera = Cast<AInteligentCamera>(UGameplayStatics::GetActorOfClass(GetWorld(), AInteligentCamera::StaticClass()));
	Camera->AddActorToWatchlist(GetOwner());
	bHasBeenAdded = true;
}

