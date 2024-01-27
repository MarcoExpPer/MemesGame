// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ThrowableItem.generated.h"

DECLARE_DELEGATE(FOnPickedFromFloor)

class UInteractableComponent;
class UFollowedByCameraComponent;

UCLASS()
class MEMESGAMES_API AThrowableItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AThrowableItem();

	void Throw(APawn* actor);

	UPROPERTY(EditDefaultsOnly)
	UFollowedByCameraComponent* FollowCameraComp;

	UPROPERTY(EditDefaultsOnly)
	UInteractableComponent* InteractableComp;

	UPROPERTY(EditDefaultsOnly)
	UClass* ItemToSpawnClass;

	FOnPickedFromFloor OnPickedFromFloor;
protected:

	virtual void BeginPlay() override;

	virtual void Interacted(AActor* actor);
};
