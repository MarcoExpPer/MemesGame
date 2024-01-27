// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractableComponent.generated.h"

DECLARE_DELEGATE_OneParam(FOnInteract, AActor*)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MEMESGAMES_API UInteractableComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractableComponent();
	
	void Interact(AActor* Interactor);

	FOnInteract* GetOnInteract() { return &OnInteract; }
	bool CanBeInteracted() { return bCanBeInteracted;  }

private:
	FOnInteract OnInteract;
	bool bCanBeInteracted = true;
};
