// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ThrowableSpawner.generated.h"


class AThrowableItem;

UCLASS()
class MEMESGAMES_API AThrowableSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AThrowableSpawner();

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	TArray<TSubclassOf<AThrowableItem>> AvailableThrowables;

	//Cooldown applies after the player picks the item
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	float Cooldown = 10.f;
	//Randomness applied to the cooldown to add variety
	float CooldownRngDelta = 3.f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	TSubclassOf<AThrowableItem> GetRandomItemClass();

	void SpawnItem();

	UFUNCTION()
	void OnSpawnedItemPicked();
};
