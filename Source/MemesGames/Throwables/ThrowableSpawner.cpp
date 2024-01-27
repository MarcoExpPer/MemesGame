// Fill out your copyright notice in the Description page of Project Settings.


#include "ThrowableSpawner.h"
#include "ThrowableItem.h"

// Sets default values
AThrowableSpawner::AThrowableSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AThrowableSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnItem();
}

TSubclassOf<AThrowableItem> AThrowableSpawner::GetRandomItemClass()
{
	int RandomIndex = FMath::RandRange(0, AvailableThrowables.Num() -1);
	return AvailableThrowables[RandomIndex];
}

void AThrowableSpawner::SpawnItem() {
	FActorSpawnParameters SpawnParams;

	AThrowableItem* SpawnedItem = Cast<AThrowableItem>(
		GetWorld()->SpawnActor<AThrowableItem>(GetRandomItemClass(), GetActorLocation(), GetActorRotation(), SpawnParams));

	SpawnedItem->OnPickedFromFloor.BindUObject(this, &AThrowableSpawner::OnSpawnedItemPicked);
}

void AThrowableSpawner::OnSpawnedItemPicked()
{
	float RandomSpawnCooldown = FMath::FRandRange(-CooldownRngDelta, CooldownRngDelta);

	FTimerHandle UselessHandle;
	GetWorldTimerManager().SetTimer(UselessHandle, this, &AThrowableSpawner::SpawnItem, RandomSpawnCooldown + Cooldown, false);
}


