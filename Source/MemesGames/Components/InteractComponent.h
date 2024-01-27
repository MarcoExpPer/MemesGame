// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MEMESGAMES_API UInteractComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UInteractComponent();

	void Interact();

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	float InteractRadius = 100.f;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	float InteractRange = 75.f;

};
